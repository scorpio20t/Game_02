// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnyKeyPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamepadUseChange, bool, GamepadUsed);

UCLASS()
class GAME_02_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "MyGameInstance")
	FOnAnyKeyPressed OnAnyKeyPressed;
	
	UPROPERTY(BlueprintAssignable, Category = "MyGameInstance")
	FOnGamepadUseChange OnGamepadUseChange;

	UPROPERTY(BlueprintReadOnly, Category = "MyGameInstance")
	bool bGamepadUsed;

	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	void OnAnyKey(bool Gamepad);
	
};
