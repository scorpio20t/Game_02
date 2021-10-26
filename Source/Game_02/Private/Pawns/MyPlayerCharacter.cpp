// Copyright by LG7


#include "Pawns/MyPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/WeaponComponent.h"
#include "Components/DecalComponent.h"
#include "Components/ArrowComponent.h"
#include "GlobalFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BrushComponent.h"
#include "GameFramework/PlayerController.h"
#include "Controllers/MyPlayerController.h"

AMyPlayerCharacter::AMyPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);

	AimHelper = CreateDefaultSubobject<UArrowComponent>("AimHelper");
	AimHelper->SetupAttachment(RootComponent);
	AimHelper->SetHiddenInGame(true);
}

void AMyPlayerCharacter::MoveForward(float AxisValue)
{
	FVector ForwardMovementVector = FVector(UKismetMathLibrary::Abs(AxisValue), 0.f, 0.f);
	AddMovementInput(ForwardMovementVector, AxisValue);
}

void AMyPlayerCharacter::MoveRight(float AxisValue)
{
	FVector RightMovementVector = FVector(0.f, UKismetMathLibrary::Abs(AxisValue), 0.f);
	AddMovementInput(RightMovementVector, AxisValue);
}

void AMyPlayerCharacter::AimY(float AxisValue)
{
	AimXValue = AxisValue;
}

void AMyPlayerCharacter::AimX(float AxisValue)
{
	AimYValue = AxisValue;
}

void AMyPlayerCharacter::StartFire()
{
	if (bCanShoot)
	{
		WeaponComponent->StartFire();
	}
}

void AMyPlayerCharacter::StopFire()
{
	WeaponComponent->StopFire();
}

void AMyPlayerCharacter::SetGamepadAimRotation()
{
	if (IsAimingWithGamepad())
	{
		AimRotationWithGamepad = UKismetMathLibrary::Conv_VectorToRotator(FVector(AimXValue, AimYValue, 0.f));
	}
	else
	{
		AimRotationWithGamepad = GetActorRotation();
	}

	AimHelper->SetWorldRotation(AimRotationWithGamepad);
}

FRotator AMyPlayerCharacter::GetAimRotationFromCursor()
{
	FVector ToVector = FVector(CursorToWorld->GetComponentLocation().X, CursorToWorld->GetComponentLocation().Y, GetActorLocation().Z);
	
	return UKismetMathLibrary::Conv_VectorToRotator(UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), ToVector));
}

void AMyPlayerCharacter::HandleCursorVisibilityAndLocation()
{
	if (UGlobalFunctionLibrary::IsGamepadUsed(this))
	{
		CursorToWorld->SetVisibility(false);
	}
	else
	{
		CursorToWorld->SetVisibility(true);

		FHitResult HitResult;
		MyPlayerController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);
		CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, UKismetMathLibrary::MakeRotationFromAxes(HitResult.ImpactNormal, FVector::ZeroVector, FVector::ZeroVector));
		AimHelper->SetWorldRotation(GetAimRotationFromCursor());

		if (ShowCursorWhenMouseOver(HitResult.GetComponent()))
		{
			MyPlayerController->CurrentMouseCursor = EMouseCursor::Default;
		}
		else
		{
			MyPlayerController->CurrentMouseCursor = EMouseCursor::Crosshairs;
		}
	}
}

void AMyPlayerCharacter::HandleCharacterAimingRotation()
{
	FRotator TargetAimRotation;
	if (UGlobalFunctionLibrary::IsGamepadUsed(this))
	{
		TargetAimRotation = AimRotationWithGamepad; //TODO - try using a function returning the required FRotator
	}
	else
	{
		TargetAimRotation = GetAimRotationFromCursor();
	}

	FRotator NewRotation = 
		UKismetMathLibrary::RInterpTo(GetControlRotation(), TargetAimRotation, GetWorld()->GetDeltaSeconds(), AimRotationInterpSpeed);

	MyPlayerController->SetControlRotation(NewRotation);
}

bool AMyPlayerCharacter::ShowCursorWhenMouseOver(UPrimitiveComponent* Target)
{
	if (Target)
	{
		if (Cast<UBrushComponent>(Target))
		{
			return true;
		}
		else if (Target->bReceivesDecals)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}

bool AMyPlayerCharacter::IsAimingWithGamepad()
{
	return UKismetMathLibrary::Abs(MyPlayerInputComponent->GetAxisValue("AimY")) > 0.1f
		|| UKismetMathLibrary::Abs(MyPlayerInputComponent->GetAxisValue("AimX")) > 0.1f;
}

void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	WeaponComponent = FindComponentByClass<UWeaponComponent>();
}

void AMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleCursorVisibilityAndLocation();
	
	if (UGlobalFunctionLibrary::IsGamepadUsed(this))
	{
		SetGamepadAimRotation();
	}

	HandleCharacterAimingRotation();
}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	MyPlayerInputComponent = PlayerInputComponent;

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("AimY", this, &AMyPlayerCharacter::AimY);
	PlayerInputComponent->BindAxis("AimX", this, &AMyPlayerCharacter::AimX);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AMyPlayerCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &AMyPlayerCharacter::StopFire);
}

