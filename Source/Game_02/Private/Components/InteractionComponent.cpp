// Copyright by LG7


#include "Components/InteractionComponent.h"


UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

}

void UInteractionComponent::SetInteractionCollision(UPrimitiveComponent* Collision)
{
	InteractionCollision = Collision;

	InteractionCollision->OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::OnInteractionInRangeInternal);
	InteractionCollision->OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::OnInteractionOutOfRangeInternal);
}

void UInteractionComponent::OnInteractionInRangeInternal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnInteractionInRange.Broadcast(OtherActor);
}

void UInteractionComponent::OnInteractionOutOfRangeInternal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnInteractionOutOfRange.Broadcast(OtherActor);
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

