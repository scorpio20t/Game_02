// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetHealthPercentage() const
{
	return CurrentHealth / MaxHealth;
}

void UHealthComponent::MakeDead()
{
	CurrentHealth = 0;
	bIsAlive = false;

	if (DeathAnimation && CharacterOwner)
	{
		CharacterOwner->PlayAnimMontage(DeathAnimation, 1.f, FName(""));
	}

	OnDeath.Broadcast();
}

float UHealthComponent::HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (bIsAlive && bCanBeDamaged)
	{
		CurrentHealth -= Damage;

		if (CurrentHealth <= 0)
		{
			MakeDead();
		}
	}
	return CurrentHealth;
}

void UHealthComponent::Heal()
{
	CurrentHealth = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	CharacterOwner = Cast<ACharacter>(GetOwner());

	DamageTaken.BindUFunction(this, "HandleDamage");
	if (CharacterOwner)
	{
		CharacterOwner->OnTakeAnyDamage.Add(DamageTaken);
	}
	else
	{
		GetOwner()->OnTakeAnyDamage.Add(DamageTaken);
	}
	
}

