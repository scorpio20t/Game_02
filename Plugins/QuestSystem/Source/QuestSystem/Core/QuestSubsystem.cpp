// Copyright by LG7


#include "QuestSubsystem.h"
#include "Quest.h"
#include "QuestMarker.h"

UQuest* UQuestSubsystem::GetActivatedQuest(const TSubclassOf<UQuest> Quest) const
{
	for (int i=0; i<ActivatedQuests.Num(); i++)
	{		
		if (ActivatedQuests[i]->QuestDataTable.RowName == Quest->GetDefaultObject<UQuest>()->QuestDataTable.RowName)
		{
			return ActivatedQuests[i];
		}
	}

	return nullptr;
}

bool UQuestSubsystem::CanActivateQuest(const UQuest* Quest) const
{
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
	}

	return false;
}

bool UQuestSubsystem::IsCurrentQuest(const TSubclassOf<UQuest> Quest) const
{
	return IsCurrentQuest_Internal(GetActivatedQuest(Quest));
}

bool UQuestSubsystem::IsCurrentQuest_Internal(UQuest* Quest) const
{
	return Quest == CurrentQuest;
}

void UQuestSubsystem::SetCurrentQuest(UQuest* Quest)
{
	UQuest* PreviousQuest = nullptr;
	
	if (CurrentQuest)
	{
		PreviousQuest = CurrentQuest;
	}
	CurrentQuest = Quest;
	CurrentQuest->InitQuest();
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
	if (IsCurrentQuest_Internal(Quest)) //TODO - perhaps it's better to pass this bool via delegate
	{
		OnQuestMarkerActivated.Broadcast(Quest->QuestMarker);
	}
}

void UQuestSubsystem::DeactivateQuestMarker_Internal(UQuest* Quest)
{
	if (Quest->QuestMarker)
	{
		Quest->QuestMarker->Disable();
		//Quest->QuestMarker = nullptr;
		OnQuestMarkerDeactivated.Broadcast();
	}
}

void UQuestSubsystem::ActivateQuest(const TSubclassOf<UQuest> Quest)
{
	if (UQuest* QuestToActivate = GetActivatedQuest(Quest))
	{
		if (CanActivateQuest(QuestToActivate))
		{
			SetCurrentQuest(QuestToActivate);
		}
	}
	else
	{
		UQuest* NewQuest = NewObject<UQuest>(this, NAME_None, RF_NoFlags, Quest->GetDefaultObject());
		SetCurrentQuest(NewQuest);
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
			if (IsCurrentQuest(Quest)) //TODO - perhaps it's better to pass this bool via delegate
			{
				OnQuestStageChanged.Broadcast(QuestToUpdate);
			}
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
			if (IsCurrentQuest(Quest)) //TODO - perhaps it's better to pass this bool via delegate
			{
				OnQuestStateChanged.Broadcast(QuestToFinish, NewState);
			}
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
