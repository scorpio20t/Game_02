// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Objectives/ObjectiveMarker.h"
#include "Components/CanvasPanelSlot.h"

FVector2D UPlayerHUD::GetWidgetPositionFromWorldLocation(FVector WorldPosition, float ViewportPercentage, FVector2D& Position)
{
	FVector2D UnclampedPosition;
	UGameplayStatics::ProjectWorldToScreen
	(UGameplayStatics::GetPlayerController(this, 0), WorldPosition, UnclampedPosition);

	float ClampedPositionX =
		UKismetMathLibrary::MapRangeClamped
		(UKismetMathLibrary::Clamp(UnclampedPosition.X, 0, UWidgetLayoutLibrary::GetViewportSize(this).X),
			0,
			UWidgetLayoutLibrary::GetViewportSize(this).X,
			UWidgetLayoutLibrary::GetViewportSize(this).X - (UWidgetLayoutLibrary::GetViewportSize(this).X * ViewportPercentage),
			UWidgetLayoutLibrary::GetViewportSize(this).X * ViewportPercentage);
	float ClampedPositionY =
		UKismetMathLibrary::MapRangeClamped
		(UKismetMathLibrary::Clamp(UnclampedPosition.Y, 0, UWidgetLayoutLibrary::GetViewportSize(this).Y),
			0,
			UWidgetLayoutLibrary::GetViewportSize(this).Y,
			UWidgetLayoutLibrary::GetViewportSize(this).Y - (UWidgetLayoutLibrary::GetViewportSize(this).Y * ViewportPercentage),
			UWidgetLayoutLibrary::GetViewportSize(this).Y * ViewportPercentage);

	return FVector2D(ClampedPositionX, ClampedPositionY) * FMath::Pow(UWidgetLayoutLibrary::GetViewportScale(this), -1.f);
}

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (ObjectiveMarkerRef && ObjectiveMarkerRef->WasRecentlyRendered())
	{
		ObjectiveMarkerWidget->SetVisibility(ESlateVisibility::Visible);
		
		FVector2D FinalMarkerPosition;
		UWidgetLayoutLibrary::SlotAsCanvasSlot(ObjectiveMarkerWidget)->SetPosition(GetWidgetPositionFromWorldLocation(ObjectiveMarkerRef->GetActorLocation(), 0.95f, FinalMarkerPosition));
	}
	else
	{
		ObjectiveMarkerWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

