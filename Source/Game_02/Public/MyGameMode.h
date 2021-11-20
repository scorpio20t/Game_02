// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAME_02_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "MyGameMode")
	void OnStartPlay();
};
