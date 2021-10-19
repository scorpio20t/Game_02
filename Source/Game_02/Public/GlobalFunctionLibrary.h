// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GlobalFunctionLibrary.generated.h"

class UMyGameInstance;

UCLASS()
class GAME_02_API UGlobalFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UMyGameInstance* GetMyGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static bool IsGamepadUsed(const UObject* WorldContextObject);
};
