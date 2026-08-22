// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDFGameMode_Game.generated.h"

class ATDFCitizenManager;
class UAllBuildingsDataAsset;
class UAllResourcesDataAsset;
class UProgressionTreeDataAsset;
class UAllBuildingCategoriesDataAsset;

UCLASS()
class THEDARKFRONTIER_API ATDFGameMode_Game :
	public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Citizens")
	TSubclassOf<ATDFCitizenManager> CitizenManagerClass;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Buildings")
	TObjectPtr<UAllBuildingsDataAsset> AllBuildings;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Resources")
	TObjectPtr<UAllResourcesDataAsset> AllResources;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression")
	TObjectPtr<UProgressionTreeDataAsset> SettlementProgression;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Buildings")
	TObjectPtr<UAllBuildingCategoriesDataAsset> AllBuildingCategories;
};