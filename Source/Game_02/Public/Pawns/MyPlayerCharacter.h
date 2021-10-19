// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayerCharacter.generated.h"

class UWeaponComponent;
class AMyPlayerController;

UCLASS()
class GAME_02_API AMyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, Category = "PlayerCharacter")
	FRotator GetAimRotationFromCursor();

	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter")
	void HandleCursorVisibilityAndLocation();

	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter")
	void HandleCharacterAimingRotation();

	UFUNCTION(BlueprintPure, Category = "PlayerCharacter")
	UPARAM(DisplayName = "Show") bool ShowCursorWhenMouseOver(UPrimitiveComponent* Target);

	UFUNCTION(BlueprintPure, Category = "PlayerCharacter")
	bool IsAimingWithGamepad();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	float AimRotationInterpSpeed = 20.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	UDecalComponent* CursorToWorld = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	UArrowComponent* AimHelper = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "PlayerCharacter")
	FRotator AimRotationWithGamepad;

	UPROPERTY(BlueprintReadWrite, Category = "PlayerCharacter")
	bool bCanShoot = true;

protected:
	virtual void BeginPlay() override;

private:
	AMyPlayerController* MyPlayerController = nullptr;
	UWeaponComponent* WeaponComponent = nullptr;
	UInputComponent* MyPlayerInputComponent = nullptr;
	
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void StartFire();
	void StopFire();
};
