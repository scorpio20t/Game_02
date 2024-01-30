// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestSubsystem.h"
#include "Quest.generated.h"

UCLASS(Blueprintable, BlueprintType)
class QUESTSYSTEM_API UQuest : public UObject
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FDataTableRowHandle QuestDataTable;

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	EQuestState QuestState;

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	FText QuestName;

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	TArray<FText> QuestObjectives;

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	int32 QuestStage; //TODO - perhaps not int?

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	class AQuestMarker* QuestMarker;

	void InitQuest();

};
