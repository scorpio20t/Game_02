// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestMarker.generated.h"

UCLASS()
class QUESTSYSTEM_API AQuestMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuestMarker();

	UFUNCTION(BlueprintCallable, Category = "ObjectiveMarker")
	void Enable();
	
	UFUNCTION(BlueprintCallable, Category = "ObjectiveMarker")
	void Disable();

};
