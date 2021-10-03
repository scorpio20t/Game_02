// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class GAME_02_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void InitWeapon(USkeletalMeshComponent* _AnimatedMesh, AController* _DamageInstigator, AActor* _WeaponOwner, USceneComponent* _AttachComponent);

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void StartFire();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void StopFire();

	UPROPERTY(BlueprintReadOnly, Category="Weapon")
	AActor* WeaponOwner = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName AttachSocketName;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	AController* DamageInstigator = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	APawn* WeaponPawnOwner = nullptr;
	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* AnimatedMesh = nullptr;

protected:
	virtual void BeginPlay() override;
};
