// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDFGameMode_Game.generated.h"

class ATDFCitizenManager;
class ATDFPlacementManager;
class ATDFRoadActor;
class ABuildingActor;

class UAllBuildingsDataAsset;
class UAllBuildingCategoriesDataAsset;
class UAllProgressionDataAsset;
class UAllResourcesDataAsset;
class UAllFoliageResourcesDataAsset;
class UAllRecipesDataAsset;
class UAllRoadsDataAsset;

class USettlementDataObject;
class UTDFSaveGame;

UCLASS()
class THEDARKFRONTIER_API ATDFGameMode_Game :
	public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	//-------------------------------------------------------------------------
	// Citizens
	//-------------------------------------------------------------------------

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Citizens")
	TSubclassOf<ATDFCitizenManager>
		CitizenManagerClass;

	//-------------------------------------------------------------------------
	// Buildings
	//-------------------------------------------------------------------------

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Buildings")
	TObjectPtr<UAllBuildingsDataAsset>
		AllBuildings;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Buildings")
	TObjectPtr<UAllBuildingCategoriesDataAsset>
		AllBuildingCategories;

	//-------------------------------------------------------------------------
	// Roads
	//-------------------------------------------------------------------------

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Roads")
	TObjectPtr<UAllRoadsDataAsset>
		AllRoads;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Roads")
	TSubclassOf<ATDFRoadActor>
		RoadActorClass;

	//-------------------------------------------------------------------------
	// Resources
	//-------------------------------------------------------------------------

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Resources")
	TObjectPtr<UAllResourcesDataAsset>
		AllResources;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Resources")
	TObjectPtr<UAllFoliageResourcesDataAsset>
		AllFoliageResources;

	//-------------------------------------------------------------------------
	// Recipes
	//-------------------------------------------------------------------------

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Recipes")
	TObjectPtr<UAllRecipesDataAsset>
		AllRecipes;

	//-------------------------------------------------------------------------
	// Progression
	//-------------------------------------------------------------------------

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression")
	TObjectPtr<UAllProgressionDataAsset>
		AllProgression;

private:

	ATDFPlacementManager* FindPlacementManager() const;

	//-------------------------------------------------------------------------
	// Restore
	//-------------------------------------------------------------------------

	ABuildingActor* RestoreSettlementBuildings(
		USettlementDataObject* Settlement,
		const UTDFSaveGame* SaveGame,
		ATDFPlacementManager* PlacementManager);

	void RestoreSettlementRoads(
		USettlementDataObject* Settlement,
		const UTDFSaveGame* SaveGame);

	void RestoreSettlementWorkplaces(
		USettlementDataObject* Settlement,
		const UTDFSaveGame* SaveGame);

	void InitializeSettlementCitizens(
		USettlementDataObject* Settlement,
		bool bLoadedGame,
		ABuildingActor* CitizenSpawnBuilding);
};