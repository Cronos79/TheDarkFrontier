// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDFBuildRoadButtonWidget.generated.h"

class UButton;
class UImage;
class UTDFRoadDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FTDFBuildRoadSelectedSignature,
	UTDFRoadDataAsset*,
	RoadData);

UCLASS(Abstract, Blueprintable)
class THEDARKFRONTIER_API UTDFBuildRoadButtonWidget :
	public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintCallable,
		Category = "Build Menu")
	void InitializeRoad(
		UTDFRoadDataAsset* InRoadData);

	UFUNCTION(
		BlueprintPure,
		Category = "Build Menu")
	UTDFRoadDataAsset* GetRoadData() const;

	UPROPERTY(
		BlueprintAssignable,
		Category = "Build Menu")
	FTDFBuildRoadSelectedSignature
		OnRoadSelected;

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(
		meta = (BindWidget))
	TObjectPtr<UButton>
		Button_Road;

	UPROPERTY(
		meta = (BindWidget))
	TObjectPtr<UImage>
		Image_Icon;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Build Menu")
	TObjectPtr<UTDFRoadDataAsset>
		RoadData;

private:

	UFUNCTION()
	void HandleRoadClicked();

	void RefreshRoadVisuals();
};