// Copyright by LG7


#include "Quest.h"
#include "Engine/DataTable.h"

void UQuest::InitQuest()
{
	QuestName = QuestDataTable.GetRow<FQuestInfo>(QuestDataTable.RowName.ToString())->QuestName;
	QuestObjectives = QuestDataTable.GetRow<FQuestInfo>(QuestDataTable.RowName.ToString())->QuestObjectives;
	QuestState = EQuestState::ACTIVE;
}

