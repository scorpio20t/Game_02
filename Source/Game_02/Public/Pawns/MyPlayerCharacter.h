// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayerCharacter.generated.h"

class UWeaponComponent;

UCLASS()
class GAME_02_API AMyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite)
	bool bCanShoot = false;

protected:
	virtual void BeginPlay() override;

private:
	UWeaponComponent* WeaponComponent = nullptr;
	
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void StartFire();
	void StopFire();
};
