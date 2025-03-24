// Copyright by LG7


#include "GlobalFunctionLibrary.h"
#include "MyGameInstance.h"
#include "MyGameMode.h"
#include "Engine/World.h"
#include "Misc/ConfigCacheIni.h"
#include "Kismet/GameplayStatics.h"

UMyGameInstance* UGlobalFunctionLibrary::GetMyGameInstance(const UObject* WorldContextObject)
{
	return Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
}

bool UGlobalFunctionLibrary::IsGamepadUsed(const UObject* WorldContextObject)
{
	return GetMyGameInstance(WorldContextObject)->bGamepadUsed;
}

FString UGlobalFunctionLibrary::GetProjectVersion(const UObject* WorldContextObject)
{
	FString ProjectVersion;
	GConfig->GetString(TEXT("/Script/EngineSettings.GeneralProjectSettings"), TEXT("ProjectVersion"), ProjectVersion, GGameIni);
	return ProjectVersion;
}
