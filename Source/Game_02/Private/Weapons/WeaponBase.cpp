// Copyright by LG7


#include "Weapons/WeaponBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWeaponBase::InitWeapon(USkeletalMeshComponent* _AnimatedMesh, AController* _DamageInstigator, AActor* _WeaponOwner, USceneComponent* _AttachComponent)
{
	if (_AnimatedMesh != nullptr)
	{
		AnimatedMesh = _AnimatedMesh;
	}
	if (_DamageInstigator != nullptr)
	{
		DamageInstigator = _DamageInstigator;
	}
	
	WeaponOwner = _WeaponOwner;

	if (Cast<APawn>(WeaponOwner))
	{
		WeaponPawnOwner = Cast<APawn>(WeaponOwner);
	}

	FAttachmentTransformRules AttachmentRules = 
		FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);

	AttachToComponent(_AttachComponent, AttachmentRules, AttachSocketName);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

