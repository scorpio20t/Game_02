// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Player.generated.h"

/**
 * 
 */
UCLASS()
class GAME_02_API UGameplayAbility_Player : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:
	TWeakObjectPtr<class AMyPlayerCharacter> OwningPlayerCharacter;
};
