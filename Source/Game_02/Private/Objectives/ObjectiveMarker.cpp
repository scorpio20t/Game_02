// Copyright by LG7


#include "Objectives/ObjectiveMarker.h"

AObjectiveMarker::AObjectiveMarker()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AObjectiveMarker::Disable()
{
	SetActorHiddenInGame(true);
}

