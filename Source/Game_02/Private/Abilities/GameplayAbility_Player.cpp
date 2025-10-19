// Copyright by LG7


#include "Abilities/GameplayAbility_Player.h"
#include "Pawns/MyPlayerCharacter.h"

void UGameplayAbility_Player::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	OwningPlayerCharacter = Cast<AMyPlayerCharacter>(GetOwningActorFromActorInfo());
}
