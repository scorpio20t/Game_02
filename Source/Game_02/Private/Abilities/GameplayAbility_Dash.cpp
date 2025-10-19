// Copyright by LG7


#include "Abilities/GameplayAbility_Dash.h"
#include "Pawns/MyPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GlobalFunctionLibrary.h"

void UGameplayAbility_Dash::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (OwningPlayerCharacter.Get())
	{
		CharacterMovementComponent = OwningPlayerCharacter->FindComponentByClass<UCharacterMovementComponent>();
	}
}

void UGameplayAbility_Dash::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	Dash();
}

void UGameplayAbility_Dash::Dash()
{
	if (CharacterMovementComponent.Get())
	{
		CharacterMovementComponent->BrakingFrictionFactor = 0.2f;
		FVector LastControlInputVector = OwningPlayerCharacter->GetLastMovementInputVector();

		if (OwningPlayerCharacter->GetLastMovementInputVector().SizeSquared() > 0.1f)
		{
			OwningPlayerCharacter->LaunchCharacter(LastControlInputVector * DashMultiplier, false, false);
		}
		else
		{
			OwningPlayerCharacter->LaunchCharacter(OwningPlayerCharacter->GetActorForwardVector() * DashMultiplier, false, false);
		}

		if (DashMontage)
		{
			GetAbilitySystemComponentFromActorInfo()->PlayMontage(this, CurrentActivationInfo, DashMontage, 1.0f);
		}
		
		UGlobalFunctionLibrary::InvokeFunction(this, "StopDash", DashLength, false);
	}
}

void UGameplayAbility_Dash::StopDash()
{
	CharacterMovementComponent->BrakingFrictionFactor = 2.f;
	K2_EndAbility();
}