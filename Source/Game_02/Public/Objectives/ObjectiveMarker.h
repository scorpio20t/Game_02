// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectiveMarker.generated.h"

UCLASS()
class GAME_02_API AObjectiveMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	AObjectiveMarker();

	UFUNCTION(BlueprintCallable, Category = "ObjectiveMarker")
	void Disable();

};
