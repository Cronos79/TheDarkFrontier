// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#include "UI/Build/TDFBuildRoadButtonWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Roads/Data/TDFRoadDataAsset.h"

void UTDFBuildRoadButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Road)
	{
		Button_Road->OnClicked.AddUniqueDynamic(
			this,
			&UTDFBuildRoadButtonWidget::HandleRoadClicked);
	}

	RefreshRoadVisuals();
}

void UTDFBuildRoadButtonWidget::InitializeRoad(
	UTDFRoadDataAsset* InRoadData)
{
	if (!InRoadData)
	{
		return;
	}

	RoadData =
		InRoadData;

	RefreshRoadVisuals();
}

UTDFRoadDataAsset*
UTDFBuildRoadButtonWidget::GetRoadData() const
{
	return RoadData;
}

void UTDFBuildRoadButtonWidget::HandleRoadClicked()
{
	if (!RoadData)
	{
		return;
	}

	OnRoadSelected.Broadcast(
		RoadData);
}

void UTDFBuildRoadButtonWidget::RefreshRoadVisuals()
{
	if (!RoadData ||
		!Image_Icon ||
		!Button_Road)
	{
		return;
	}

	if (RoadData->Icon)
	{
		Image_Icon->SetBrushFromTexture(
			RoadData->Icon,
			true);
	}

	Button_Road->SetToolTipText(
		RoadData->DisplayName);
}