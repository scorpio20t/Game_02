// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AWeaponBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class GAME_02_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	UFUNCTION(BlueprintCallable, Category = "WeaponComponent")
	void InitWeapon(USkeletalMeshComponent* _AnimatedMesh, AController* _DamageInstigator, AActor* _WeaponOwner, USceneComponent* _AttachComponent);
	UFUNCTION(BlueprintCallable, Category = "WeaponComponent")
	void StartFire();
	UFUNCTION(BlueprintCallable, Category = "WeaponComponent")
	void StopFire();

	UPROPERTY(EditAnywhere, Category="WeaponComponent")
	TSubclassOf<AWeaponBase> WeaponClass = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "WeaponComponent")
	AWeaponBase* WeaponRef = nullptr;		
};