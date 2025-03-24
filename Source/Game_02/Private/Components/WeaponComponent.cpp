// Copyright by LG7


#include "Components/WeaponComponent.h"
#include "Weapons/WeaponBase.h"
#include "Engine/World.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UWeaponComponent::InitWeapon(USkeletalMeshComponent* _AnimatedMesh, AController* _DamageInstigator, AActor* _WeaponOwner, USceneComponent* _AttachComponent)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	WeaponRef = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, _AttachComponent->GetComponentTransform(), SpawnParameters);
	WeaponRef->InitWeapon(_AnimatedMesh, _DamageInstigator, _WeaponOwner, _AttachComponent);
}

void UWeaponComponent::StartFire()
{
	WeaponRef->StartFire();
}

void UWeaponComponent::StopFire()
{
	WeaponRef->StopFire();
}



