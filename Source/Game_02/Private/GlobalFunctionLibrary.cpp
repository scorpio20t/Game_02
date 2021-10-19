// Copyright by LG7


#include "GlobalFunctionLibrary.h"
#include "MyGameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UMyGameInstance* UGlobalFunctionLibrary::GetMyGameInstance(const UObject* WorldContextObject)
{
	return Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
}

bool UGlobalFunctionLibrary::IsGamepadUsed(const UObject* WorldContextObject)
{
	return GetMyGameInstance(WorldContextObject)->bGamepadUsed;
}