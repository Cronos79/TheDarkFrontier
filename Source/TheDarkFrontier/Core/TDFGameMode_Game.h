// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDFGameMode_Game.generated.h"

class ATDFCitizenManager;
class ATDFPlacementManager;
class ABuildingActor;
class UAllBuildingsDataAsset;
class UAllBuildingCategoriesDataAsset;
class UAllProgressionDataAsset;
class UAllResourcesDataAsset;
class UAllFoliageResourcesDataAsset;
class UAllRecipesDataAsset;
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

	void RestoreSettlementWorkplaces(
		USettlementDataObject* Settlement,
		const UTDFSaveGame* SaveGame);

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Citizens")
	TSubclassOf<ATDFCitizenManager>
		CitizenManagerClass;

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

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Recipes")
	TObjectPtr<UAllRecipesDataAsset>
		AllRecipes;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression")
	TObjectPtr<UAllProgressionDataAsset>
		AllProgression;

private:

	ATDFPlacementManager* FindPlacementManager() const;

	ABuildingActor* RestoreSettlementBuildings(
		USettlementDataObject* Settlement,
		const UTDFSaveGame* SaveGame,
		ATDFPlacementManager* PlacementManager);

	void InitializeSettlementCitizens(
		USettlementDataObject* Settlement,
		bool bLoadedGame,
		ABuildingActor* CitizenSpawnBuilding);
};