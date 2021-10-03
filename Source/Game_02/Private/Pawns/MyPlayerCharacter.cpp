// Copyright by LG7


#include "Pawns/MyPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/WeaponComponent.h"

AMyPlayerCharacter::AMyPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
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

void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	WeaponComponent = FindComponentByClass<UWeaponComponent>();
}

void AMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AMyPlayerCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &AMyPlayerCharacter::StopFire);
}

