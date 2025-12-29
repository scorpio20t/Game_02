// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "MyPlayerCharacter.generated.h"

UCLASS()
class GAME_02_API AMyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPlayerCharacter")
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPlayerCharacter")
	TObjectPtr<class UHealthComponent> HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPlayerCharacter")
	TObjectPtr<class UWeaponComponent> WeaponComponent;
	//---------------

	//Player Abilities
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	int32 FireAbilityInputID = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	TSubclassOf<class UGameplayAbility> FireAbility;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	TSubclassOf<class UGameplayAbility> DashAbility;
	//---------------
	
	UPROPERTY(BlueprintReadWrite, Category = "PlayerCharacter")
	bool bCanShoot = true;

	/*Player rotation-to-cursor ratio*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	float AimRotationInterpSpeed = 20.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	TObjectPtr<class UDecalComponent> CursorToWorld = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	TObjectPtr<class UArrowComponent> AimHelper = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	TObjectPtr<class UWidgetComponent> GamepadAimWidget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	TObjectPtr<class USceneComponent> MarkerRotator = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter")
	TObjectPtr<class UWidgetComponent> OutOfScreenMarkerWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "PlayerCharacter")
	TObjectPtr<class UPlayerHUD> PlayerHUD = nullptr;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> InputActionFire;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> InputActionDash;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> InputActionMoveForward;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> InputActionMoveRight;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> InputActionAimX;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> InputActionAimY;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<class AMyPlayerController> MyPlayerController = nullptr;

	float AimXValue;
	float AimYValue;
	
	void GiveInitialAbilities() const;
	void MoveForward(const FInputActionInstance& Instance);
	void MoveRight(const FInputActionInstance& Instance);
	void AimY(const FInputActionInstance& Instance);
	void AimX(const FInputActionInstance& Instance);
	void StartFire();
	void StopFire();
	void Dash();

	FRotator GetAimRotationFromCursor() const;
	FRotator GetAimRotationFromGamepad() const;
	void HandleCursorVisibilityAndLocation();
	void HandleCharacterAimingRotation();
	bool ShowCursorWhenMouseOver(UPrimitiveComponent* Target);
	bool IsAimingWithGamepad() const;

	void Set3DMarkerRotation();
};
