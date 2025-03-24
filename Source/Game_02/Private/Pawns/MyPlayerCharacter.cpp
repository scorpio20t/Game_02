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
#include "Components/WidgetComponent.h"
#include "UI/PlayerHUD.h"
#include "QuestSystem/Core/QuestMarker.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputAction.h"

AMyPlayerCharacter::AMyPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);

	AimHelper = CreateDefaultSubobject<UArrowComponent>("AimHelper");
	AimHelper->SetupAttachment(RootComponent);
	AimHelper->SetHiddenInGame(true);

	GamepadAimWidget = CreateDefaultSubobject<UWidgetComponent>("GamepadAimWidget");
	GamepadAimWidget->SetupAttachment(AimHelper);

	MarkerRotator = CreateDefaultSubobject<USceneComponent>("MarkerRotator");
	MarkerRotator->SetupAttachment(RootComponent);

	OutOfScreenMarkerWidget = CreateDefaultSubobject<UWidgetComponent>("OutOfScreenMarkerWidget");
	OutOfScreenMarkerWidget->SetupAttachment(MarkerRotator);
}

void AMyPlayerCharacter::MoveForward(const FInputActionInstance& Instance)
{
	float AxisValue = Instance.GetValue().Get<float>();
	FVector ForwardMovementVector = FVector(UKismetMathLibrary::Abs(AxisValue), 0.f, 0.f);
	AddMovementInput(ForwardMovementVector, AxisValue);
}

void AMyPlayerCharacter::MoveRight(const FInputActionInstance& Instance)
{
	float AxisValue = Instance.GetValue().Get<float>();
	FVector RightMovementVector = FVector(0.f, UKismetMathLibrary::Abs(AxisValue), 0.f);
	AddMovementInput(RightMovementVector, AxisValue);
}

void AMyPlayerCharacter::AimY(const FInputActionInstance& Instance)
{
	AimXValue = -Instance.GetValue().Get<float>();;
}

void AMyPlayerCharacter::AimX(const FInputActionInstance& Instance)
{
	AimYValue = Instance.GetValue().Get<float>();
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

void AMyPlayerCharacter::Dash()
{
	if (!bIsDashing)
	{
		bIsDashing = true;
		CharacterMovementComponent->BrakingFrictionFactor = 0.2f;

		if (LastControlInputVector.SizeSquared() > 0.1f)
		{
			LaunchCharacter(LastControlInputVector * DashMultiplier, false, false);
		}
		else
		{
			LaunchCharacter(GetActorForwardVector() * DashMultiplier, false, false);
		}

		UGlobalFunctionLibrary::InvokeFunction(this, "StopDash", DashLength, false);
	}
}

void AMyPlayerCharacter::StopDash()
{
	bIsDashing = false;
	CharacterMovementComponent->BrakingFrictionFactor = 2.f;
}

FRotator AMyPlayerCharacter::GetAimRotationFromGamepad()
{
	if (IsAimingWithGamepad())
	{
		return UKismetMathLibrary::Conv_VectorToRotator(FVector(AimXValue, AimYValue, 0.f));
	}
	else
	{
		return GetActorRotation();
	}	
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
		GamepadAimWidget->SetVisibility(true);
	}
	else
	{
		CursorToWorld->SetVisibility(true);
		GamepadAimWidget->SetVisibility(false);

		FHitResult HitResult;
		MyPlayerController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);
		CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, UKismetMathLibrary::MakeRotationFromAxes(HitResult.ImpactNormal, FVector::ZeroVector, FVector::ZeroVector));

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
		TargetAimRotation = GetAimRotationFromGamepad();
		AimHelper->SetWorldRotation(TargetAimRotation);
	}
	else
	{
		TargetAimRotation = GetAimRotationFromCursor();
		AimHelper->SetWorldRotation(GetAimRotationFromCursor());
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
	return UKismetMathLibrary::Abs(AimYValue) > 0.1f
		|| UKismetMathLibrary::Abs(AimXValue) > 0.1f;
}

void AMyPlayerCharacter::Set3DMarkerRotation()
{
	if (PlayerHUD && PlayerHUD->ObjectiveMarkerRef)
	{
		if (PlayerHUD->ObjectiveMarkerRef->WasRecentlyRendered())
		{
			OutOfScreenMarkerWidget->SetVisibility(false);
		}
		else
		{
			OutOfScreenMarkerWidget->SetVisibility(true);
			
			FRotator MarkerRotatorRot = 
				UKismetMathLibrary::Conv_VectorToRotator(UKismetMathLibrary::GetDirectionUnitVector
				(GetActorLocation(), 
					FVector(PlayerHUD->ObjectiveMarkerRef->GetActorLocation().X, PlayerHUD->ObjectiveMarkerRef->GetActorLocation().Y, GetActorLocation().Z)));

			MarkerRotator->SetWorldRotation(MarkerRotatorRot);
		}
	}
	else
	{
		OutOfScreenMarkerWidget->SetVisibility(false);
	}
}

void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	CharacterMovementComponent = FindComponentByClass<UCharacterMovementComponent>();
	WeaponComponent = FindComponentByClass<UWeaponComponent>();
}

void AMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleCursorVisibilityAndLocation();
	HandleCharacterAimingRotation();
	Set3DMarkerRotation();
}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MyPlayerController->GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInput->BindAction(InputActionFire, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::StartFire);
	EnhancedInput->BindAction(InputActionFire, ETriggerEvent::Completed, this, &AMyPlayerCharacter::StopFire);
	EnhancedInput->BindAction(InputActionDash, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Dash);
	EnhancedInput->BindAction(InputActionMoveForward, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::MoveForward);
	EnhancedInput->BindAction(InputActionMoveRight, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::MoveRight);
	EnhancedInput->BindAction(InputActionAimX, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::AimX);
	EnhancedInput->BindAction(InputActionAimY, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::AimY);
}

