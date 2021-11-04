// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayerCharacter.generated.h"

class UWeaponComponent;
class AMyPlayerController;
class UWidgetComponent;
class UPlayerHUD;

UCLASS()
class GAME_02_API AMyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	float AimRotationInterpSpeed = 20.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	UDecalComponent* CursorToWorld = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	UArrowComponent* AimHelper = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	UWidgetComponent* GamepadAimWidget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	USceneComponent* MarkerRotator = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	UWidgetComponent* OutOfScreenMarkerWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "PlayerCharacter")
	bool bCanShoot = true;

	UPROPERTY(BlueprintReadWrite, Category = "PlayerCharacter")
	UPlayerHUD* PlayerHUD = nullptr;

protected:
	virtual void BeginPlay() override;

private:
	AMyPlayerController* MyPlayerController = nullptr;
	UWeaponComponent* WeaponComponent = nullptr;
	UInputComponent* MyPlayerInputComponent = nullptr;

	float AimXValue;
	float AimYValue;
	
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void AimY(float AxisValue);
	void AimX(float AxisValue);
	void StartFire();
	void StopFire();

	FRotator GetAimRotationFromCursor();
	FRotator GetAimRotationFromGamepad();
	void HandleCursorVisibilityAndLocation();
	void HandleCharacterAimingRotation();
	bool ShowCursorWhenMouseOver(UPrimitiveComponent* Target);
	bool IsAimingWithGamepad();

	void Set3DMarkerRotation();
};
