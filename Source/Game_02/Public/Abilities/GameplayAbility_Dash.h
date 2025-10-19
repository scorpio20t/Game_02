// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility_Player.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Dash.generated.h"

/**
 * 
 */
UCLASS()
class GAME_02_API UGameplayAbility_Dash : public UGameplayAbility_Player
{
	GENERATED_BODY()

public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	/*Dash Montage to play*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayAbility_Dash")
	TObjectPtr<UAnimMontage> DashMontage;

	/*Determines Dash speed and distance*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayAbility_Dash")
	float DashMultiplier = 3000.f;

	/*Has to be equal to Dash Anim Sequence length, considering the Anim Sequence rate (if not 1.0)*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayAbility_Dash")
	float DashLength = 0.6f;

private:
	void Dash();

	UFUNCTION()
	void StopDash();
	
	TWeakObjectPtr<class UCharacterMovementComponent> CharacterMovementComponent;
};
