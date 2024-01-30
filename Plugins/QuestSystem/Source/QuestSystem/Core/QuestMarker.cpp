// Copyright by LG7


#include "QuestMarker.h"

AQuestMarker::AQuestMarker()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AQuestMarker::Enable()
{
	SetActorHiddenInGame(false);
}

void AQuestMarker::Disable()
{
	SetActorHiddenInGame(true);
}

