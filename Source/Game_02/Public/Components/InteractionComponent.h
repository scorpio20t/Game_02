// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionInRangeSignature, AActor*, InteractingActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionOutOfRangeSignature, AActor*, InteractingActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_02_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

	UFUNCTION(BlueprintCallable, Category = "InteractionComponent")
	void SetInteractionCollision(UPrimitiveComponent* Collision);

	UPROPERTY(BlueprintAssignable)
	FOnInteractionInRangeSignature OnInteractionInRange;
	UPROPERTY(BlueprintAssignable)
	FOnInteractionOutOfRangeSignature OnInteractionOutOfRange;

	UFUNCTION()
	void OnInteractionInRangeInternal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnInteractionOutOfRangeInternal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> InteractionCollision = nullptr;		
};