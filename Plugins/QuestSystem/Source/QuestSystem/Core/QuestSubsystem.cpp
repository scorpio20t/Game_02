// Copyright by LG7


#include "QuestSubsystem.h"
#include "Quest.h"
#include "QuestMarker.h"

UQuest* UQuestSubsystem::GetActivatedQuest(const TSubclassOf<UQuest> Quest) const
{
	for (int i=0; i<ActivatedQuests.Num(); i++)
	{		
		if (ActivatedQuests[i]->QuestSubclass == Quest)
		{
			return ActivatedQuests[i];
		}
	}

	return nullptr;
}

bool UQuestSubsystem::CanActivateQuest(const UQuest* Quest) const
{
	if (!Quest)
	{
		return false;
	}

	switch (Quest->QuestState)
	{
		case EQuestState::INACTIVE:
		{
			return true;
		}
		case EQuestState::ACTIVE:
		{
			return true;
		}
		case EQuestState::COMPLETED:
		{
			return false;
		}
		case EQuestState::FAILED:
		{
			return false;
		}
		default:
		{
			return false;
		}
	}
}

bool UQuestSubsystem::IsCurrentQuest(const TSubclassOf<UQuest> Quest) const
{
	if (UQuest* QueriedQuest = (GetActivatedQuest(Quest)))
	{
		return IsCurrentQuest_Internal(GetActivatedQuest(Quest));
	}
	return false;
}

bool UQuestSubsystem::IsCurrentQuest_Internal(UQuest* Quest) const
{
	if (Quest)
	{
		return Quest == CurrentQuest;
	}
	return false;
}

void UQuestSubsystem::SetCurrentQuest(UQuest* Quest, TSubclassOf<UQuest> QuestSubclass)
{
	UQuest* PreviousQuest = nullptr;
	
	if (CurrentQuest)
	{
		PreviousQuest = CurrentQuest;
	}
	CurrentQuest = Quest;
	CurrentQuest->InitQuest(QuestSubclass);
	OnQuestActivated.Broadcast(CurrentQuest);
	
	if (CurrentQuest->QuestMarker)
	{
		ActivateQuestMarker_Internal(CurrentQuest, CurrentQuest->QuestMarker);
	}
	else if (PreviousQuest && PreviousQuest->QuestMarker)
	{
		DeactivateQuestMarker_Internal(PreviousQuest);
	}
}

void UQuestSubsystem::ActivateQuestMarker_Internal(UQuest* Quest, AQuestMarker* QuestMarker)
{
	if (Quest->QuestMarker)
	{
		Quest->QuestMarker->Disable();
	}

	Quest->QuestMarker = QuestMarker;
	Quest->QuestMarker->Enable();
	OnQuestMarkerActivated.Broadcast(Quest->QuestMarker, IsCurrentQuest_Internal(Quest));
}

void UQuestSubsystem::DeactivateQuestMarker_Internal(UQuest* Quest)
{
	if (Quest->QuestMarker)
	{
		Quest->QuestMarker->Disable();
		OnQuestMarkerDeactivated.Broadcast();
	}
}

void UQuestSubsystem::ActivateQuest(const TSubclassOf<UQuest> Quest)
{
	if (UQuest* QuestToActivate = GetActivatedQuest(Quest))
	{
		if (CanActivateQuest(QuestToActivate))
		{
			SetCurrentQuest(QuestToActivate, Quest);
		}
	}
	else
	{
		UQuest* NewQuest = NewObject<UQuest>(this, NAME_None, RF_NoFlags, Quest->GetDefaultObject());
		SetCurrentQuest(NewQuest, Quest);
		ActivatedQuests.Add(CurrentQuest);
	}
}

void UQuestSubsystem::ChangeQuestStage(const TSubclassOf<UQuest> Quest, int32 NewStage)
{
	if (UQuest* QuestToUpdate = GetActivatedQuest(Quest))
	{
		if (QuestToUpdate->QuestState == EQuestState::ACTIVE)
		{
			QuestToUpdate->QuestStage = NewStage;
			OnQuestStageChanged.Broadcast(QuestToUpdate, IsCurrentQuest_Internal(QuestToUpdate));
		}
	}
}

void UQuestSubsystem::FinishQuest(const TSubclassOf<UQuest> Quest, EQuestState NewState)
{
	if (UQuest* QuestToFinish = GetActivatedQuest(Quest))
	{
		if (QuestToFinish->QuestState == EQuestState::ACTIVE)
		{
			QuestToFinish->QuestState = NewState;
			OnQuestStateChanged.Broadcast(QuestToFinish, NewState, IsCurrentQuest_Internal(QuestToFinish));
		}
	}
}

void UQuestSubsystem::ActivateQuestMarker(const TSubclassOf<UQuest> Quest, AQuestMarker* QuestMarker)
{
	if (UQuest* QuestToMark = GetActivatedQuest(Quest))
	{
		ActivateQuestMarker_Internal(QuestToMark, QuestMarker);
	}
}

void UQuestSubsystem::DeactivateQuestMarker(const TSubclassOf<UQuest> Quest)
{
	if (UQuest* QuestToUnmark = GetActivatedQuest(Quest))
	{
		DeactivateQuestMarker_Internal(QuestToUnmark);
	}
}

void UQuestSubsystem::ClearQuests()
{
	ActivatedQuests.Empty();
}
