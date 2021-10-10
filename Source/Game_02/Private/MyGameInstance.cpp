// Copyright by LG7


#include "MyGameInstance.h"

void UMyGameInstance::OnAnyKey(bool Gamepad)
{
	if (Gamepad != bGamepadUsed)
	{
		bGamepadUsed = Gamepad;
		OnGamepadUseChange.Broadcast(bGamepadUsed);
	}
}