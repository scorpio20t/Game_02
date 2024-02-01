// Copyright by LG7

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "QuestSubsystem.generated.h"

UENUM(BlueprintType)
enum class EQuestState : uint8
{
    INACTIVE,
    ACTIVE,
    COMPLETED,
    FAILED
};


USTRUCT(BlueprintType)
struct FQuestInfo : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
    FText QuestName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Info")
    TArray<FText> QuestObjectives;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestActivated, UQuest*, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestStageChanged, UQuest*, Quest, bool, bIsCurrentQuest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnQuestStateChanged, UQuest*, Quest, EQuestState, NewState, bool, bIsCurrentQuest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestMarkerActivated, AQuestMarker*, QuestMarker, bool, bIsCurrentQuest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestMarkerDeactivated);

class UQuest;
class AQuestMarker;

UCLASS()
class QUESTSYSTEM_API UQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestActivated OnQuestActivated;

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestStageChanged OnQuestStageChanged;

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestStateChanged OnQuestStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestMarkerActivated OnQuestMarkerActivated;
    
    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestMarkerDeactivated OnQuestMarkerDeactivated;
    
    UPROPERTY(BlueprintReadOnly, Category = "Quest")
    UQuest* CurrentQuest;

    UPROPERTY(BlueprintReadOnly, Category = "Quest")
    TArray<UQuest*> ActivatedQuests;

    UFUNCTION(BlueprintPure, Category = "Quest")
    UQuest* GetActivatedQuest(const TSubclassOf<UQuest> Quest) const;

    UFUNCTION(BlueprintPure, Category = "Quest")
    bool CanActivateQuest(const UQuest* Quest) const;

    UFUNCTION(BlueprintPure, Category = "Quest")
    bool IsCurrentQuest(const TSubclassOf<UQuest> Quest) const;
    
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void ActivateQuest(const TSubclassOf<UQuest> Quest);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    void ChangeQuestStage(const TSubclassOf<UQuest> Quest, int32 NewStage);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    void FinishQuest(const TSubclassOf<UQuest> Quest, EQuestState NewState);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    void ActivateQuestMarker(const TSubclassOf<UQuest> Quest, AQuestMarker* QuestMarker);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    void DeactivateQuestMarker(const TSubclassOf<UQuest> Quest);

    //Use to clear Quests info and reset progress
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void ClearQuests();

    //TODO Quests data should be stored somehow, so that ActivatedQuests is populated again when we're back in the game

private:
    void SetCurrentQuest(UQuest* Quest, TSubclassOf<UQuest> QuestSubclass);
    bool IsCurrentQuest_Internal(UQuest* Quest) const;
    void ActivateQuestMarker_Internal(UQuest* Quest, AQuestMarker* QuestMarker);
    void DeactivateQuestMarker_Internal(UQuest* Quest);
	
};
