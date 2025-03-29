// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class AQuestMarker;

UCLASS()
class GAME_02_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "PlayerHUD", meta=(BindWidget))
	TObjectPtr<UUserWidget> ObjectiveMarkerWidget = nullptr;
	
	UPROPERTY(BlueprintReadWrite, Category = "PlayerHUD")
	TObjectPtr<AQuestMarker> ObjectiveMarkerRef = nullptr;

protected:	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	FVector2D GetWidgetPositionFromWorldLocation(const FVector& WorldPosition, float ViewportPercentage, FVector2D& Position);

};
