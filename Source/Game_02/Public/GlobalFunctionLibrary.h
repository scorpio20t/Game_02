// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TimerManager.h"
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

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static FString GetProjectVersion(const UObject* WorldContextObject);

	template<typename... VarTypes>
	static FTimerHandle InvokeFunction(UObject* WorldContextObject, FString FunctionName, float Delay, bool bLoop, VarTypes... Vars)
	{
		FTimerHandle Handle;
		FTimerDelegate Delegate;
		FName const FunctionFName(*FunctionName);

		Delegate.BindUFunction(WorldContextObject, FunctionFName, Vars...);

		if (GEngine)
		{
			UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
			if (World)
			{
				World->GetTimerManager().SetTimer(Handle, Delegate, Delay, bLoop);
			}
		}

		return Handle;
	}
};
