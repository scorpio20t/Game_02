// Fill out your copyright notice in the Description page of Project Settings.


#include "Objectives/ObjectiveMarker.h"

// Sets default values
AObjectiveMarker::AObjectiveMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectiveMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectiveMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

