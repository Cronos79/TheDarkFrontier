// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#include "TDFGameMode_Game.h"

#include "Buildings/Actors/BuildingActor.h"
#include "Buildings/Data/BuildingDataAsset.h"
#include "Buildings/Systems/TDFPlacementManager.h"
#include "Buildings/Tags/TDFBuildingTags.h"
#include "Citizens/Systems/TDFCitizenManager.h"
#include "Jobs/Systems/TDFWorkplaceManager.h"
#include "Kismet/GameplayStatics.h"
#include "Production/Data/AllRecipesDataAsset.h"
#include "Progression/Data/AllProgressionDataAsset.h"
#include "Resources/Data/AllFoliageResourcesDataAsset.h"
#include "Resources/Inventory/TDFInventory.h"
#include "Roads/Actors/TDFRoadActor.h"
#include "Roads/Data/TDFRoadDataAsset.h"
#include "Save/Data/TDFSaveGame.h"
#include "Save/Systems/TDFSaveSubsystem.h"
#include "Settlements/Data/SettlementDataObject.h"
#include "World/Systems/TDFTimeSubsystem.h"
#include "World/Systems/TDFWorldSubsystem.h"

void ATDFGameMode_Game::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* GameInstance =
		GetGameInstance();

	if (!GameInstance)
	{
		return;
	}

	//-------------------------------------------------------------------------
	// Save State
	//-------------------------------------------------------------------------

	UTDFSaveSubsystem* SaveSubsystem =
		GameInstance->GetSubsystem<UTDFSaveSubsystem>();

	const bool bLoadedGame =
		SaveSubsystem &&
		SaveSubsystem->IsLoadedGameSession();

	UTDFSaveGame* PendingSave =
		SaveSubsystem
		? SaveSubsystem->GetPendingLoadedSave()
		: nullptr;

	//-------------------------------------------------------------------------
	// World
	//-------------------------------------------------------------------------

	UTDFWorldSubsystem* WorldSubsystem =
		GameInstance->GetSubsystem<UTDFWorldSubsystem>();

	if (!WorldSubsystem)
	{
		return;
	}

	if (AllBuildings)
	{
		WorldSubsystem->SetAllBuildings(
			AllBuildings);
	}

	if (AllBuildingCategories)
	{
		WorldSubsystem->SetAllBuildingCategories(
			AllBuildingCategories);
	}

	if (AllRoads)
	{
		WorldSubsystem->SetAllRoads(
			AllRoads);
	}

	if (AllResources)
	{
		WorldSubsystem->SetAllResources(
			AllResources);
	}

	if (AllFoliageResources)
	{
		WorldSubsystem->SetAllFoliageResources(
			AllFoliageResources);
	}

	if (AllRecipes)
	{
		WorldSubsystem->SetAllRecipes(
			AllRecipes);
	}

	//-------------------------------------------------------------------------
	// Placement Manager
	//-------------------------------------------------------------------------

	ATDFPlacementManager* PlacementManager =
		FindPlacementManager();

	//-------------------------------------------------------------------------
	// Settlements
	//-------------------------------------------------------------------------

	for (USettlementDataObject* Settlement :
		WorldSubsystem->Settlements)
	{
		if (!Settlement)
		{
			continue;
		}

		//-------------------------------------------------------------------------
		// Progression
		//-------------------------------------------------------------------------

		if (AllProgression)
		{
			Settlement->InitializeProgression(
				AllProgression);
		}

		//-------------------------------------------------------------------------
		// Restore World Actors
		//-------------------------------------------------------------------------

		ABuildingActor* CitizenSpawnBuilding =
			nullptr;

		if (bLoadedGame &&
			PendingSave)
		{
			CitizenSpawnBuilding =
				RestoreSettlementBuildings(
					Settlement,
					PendingSave,
					PlacementManager);

			RestoreSettlementRoads(
				Settlement,
				PendingSave);

			RestoreSettlementWorkplaces(
				Settlement,
				PendingSave);
		}

		//-------------------------------------------------------------------------
		// Citizens
		//-------------------------------------------------------------------------

		InitializeSettlementCitizens(
			Settlement,
			bLoadedGame,
			CitizenSpawnBuilding);
	}

	//-------------------------------------------------------------------------
	// Finish World Restore
	//-------------------------------------------------------------------------

	if (bLoadedGame &&
		PendingSave &&
		SaveSubsystem)
	{
		SaveSubsystem->MarkWorldRestoreComplete();

		UE_LOG(
			LogTemp,
			Display,
			TEXT("Load Restore | Gameplay world restore complete"));
	}

	//-------------------------------------------------------------------------
	// Time
	//-------------------------------------------------------------------------

	UTDFTimeSubsystem* TimeSubsystem =
		GameInstance->GetSubsystem<UTDFTimeSubsystem>();

	if (TimeSubsystem)
	{
		TimeSubsystem->StartTime();
	}
}

ATDFPlacementManager*
ATDFGameMode_Game::FindPlacementManager() const
{
	if (!GetWorld())
	{
		return nullptr;
	}

	return Cast<ATDFPlacementManager>(
		UGameplayStatics::GetActorOfClass(
			GetWorld(),
			ATDFPlacementManager::StaticClass()));
}

//-----------------------------------------------------------------------------
// Restore Buildings
//-----------------------------------------------------------------------------

ABuildingActor*
ATDFGameMode_Game::RestoreSettlementBuildings(
	USettlementDataObject* Settlement,
	const UTDFSaveGame* SaveGame,
	ATDFPlacementManager* PlacementManager)
{
	if (!Settlement ||
		!SaveGame ||
		!PlacementManager ||
		!GetWorld())
	{
		return nullptr;
	}

	UGameInstance* GameInstance =
		GetGameInstance();

	if (!GameInstance)
	{
		return nullptr;
	}

	UTDFWorldSubsystem* WorldSubsystem =
		GameInstance->GetSubsystem<UTDFWorldSubsystem>();

	if (!WorldSubsystem)
	{
		return nullptr;
	}

	TSubclassOf<ABuildingActor> BuildingActorClass =
		PlacementManager->GetBuildingActorClass();

	if (!BuildingActorClass)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("Load Restore | Placement Manager has no BuildingActorClass"));

		return nullptr;
	}

	const FTDFSettlementSaveData* SettlementSaveData =
		nullptr;

	for (const FTDFSettlementSaveData& Candidate :
		SaveGame->Settlements)
	{
		if (Candidate.SettlementID ==
			Settlement->SettlementID)
		{
			SettlementSaveData =
				&Candidate;

			break;
		}
	}

	if (!SettlementSaveData)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Load Restore | No save record found for settlement %s"),
			*Settlement->SettlementName);

		return nullptr;
	}

	ABuildingActor* RestoredWagon =
		nullptr;

	ABuildingActor* FallbackSpawnBuilding =
		nullptr;

	int32 RestoredBuildingCount =
		0;

	for (const FTDFBuildingSaveData& BuildingSaveData :
		SettlementSaveData->Buildings)
	{
		if (!BuildingSaveData.BuildingID.IsValid() ||
			!BuildingSaveData.BuildingTag.IsValid())
		{
			continue;
		}

		UBuildingDataAsset* BuildingData =
			WorldSubsystem->FindBuildingByTag(
				BuildingSaveData.BuildingTag);

		if (!BuildingData)
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("Load Restore | Missing BuildingData for %s"),
				*BuildingSaveData.BuildingTag.ToString());

			continue;
		}

		ABuildingActor* Building =
			GetWorld()->SpawnActorDeferred<ABuildingActor>(
				BuildingActorClass,
				BuildingSaveData.Transform);

		if (!Building)
		{
			continue;
		}

		Building->RestoreBuilding(
			BuildingData,
			BuildingSaveData.BuildingID,
			BuildingSaveData.VisualState,
			BuildingSaveData.CurrentConstructionWork);

		Building->FinishSpawning(
			BuildingSaveData.Transform);

		Settlement->RegisterBuilding(
			Building);

		UTDFInventory* BuildingInventory =
			Building->GetInventory();

		if (BuildingInventory)
		{
			BuildingInventory->RestoreItems(
				BuildingSaveData.InventoryItems);
		}

		UTDFInventory* ConstructionInventory =
			Building->GetConstructionInventory();

		if (ConstructionInventory)
		{
			ConstructionInventory->RestoreItems(
				BuildingSaveData.ConstructionInventoryItems);
		}

		RestoredBuildingCount++;

		if (!FallbackSpawnBuilding &&
			BuildingSaveData.VisualState ==
			ETDFBuildingVisualState::Permanent)
		{
			FallbackSpawnBuilding =
				Building;
		}

		if (BuildingSaveData.BuildingTag ==
			TDFBuildingTags::Building_Civic_Wagon)
		{
			RestoredWagon =
				Building;
		}
	}

	UE_LOG(
		LogTemp,
		Display,
		TEXT("Load Restore | Settlement: %s | Restored Buildings: %d"),
		*Settlement->SettlementName,
		RestoredBuildingCount);

	if (RestoredWagon)
	{
		UE_LOG(
			LogTemp,
			Display,
			TEXT("Load Restore | Citizen spawn anchor: Wagon"));

		return RestoredWagon;
	}

	if (FallbackSpawnBuilding)
	{
		UBuildingDataAsset* SpawnBuildingData =
			FallbackSpawnBuilding->GetBuildingData();

		UE_LOG(
			LogTemp,
			Display,
			TEXT("Load Restore | Citizen spawn anchor: %s"),
			SpawnBuildingData
			? *SpawnBuildingData->BuildingTag.ToString()
			: TEXT("Fallback Building"));

		return FallbackSpawnBuilding;
	}

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Load Restore | No valid citizen spawn building found for %s"),
		*Settlement->SettlementName);

	return nullptr;
}

//-----------------------------------------------------------------------------
// Restore Roads
//-----------------------------------------------------------------------------

void ATDFGameMode_Game::RestoreSettlementRoads(
	USettlementDataObject* Settlement,
	const UTDFSaveGame* SaveGame)
{
	if (!Settlement ||
		!SaveGame ||
		!GetWorld())
	{
		return;
	}

	if (!RoadActorClass)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("Load Restore | GameMode has no RoadActorClass"));

		return;
	}

	UGameInstance* GameInstance =
		GetGameInstance();

	if (!GameInstance)
	{
		return;
	}

	UTDFWorldSubsystem* WorldSubsystem =
		GameInstance->GetSubsystem<UTDFWorldSubsystem>();

	if (!WorldSubsystem)
	{
		return;
	}

	const FTDFSettlementSaveData* SettlementSaveData =
		nullptr;

	for (const FTDFSettlementSaveData& Candidate :
		SaveGame->Settlements)
	{
		if (Candidate.SettlementID ==
			Settlement->SettlementID)
		{
			SettlementSaveData =
				&Candidate;

			break;
		}
	}

	if (!SettlementSaveData)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Load Restore | No road save record found for settlement %s"),
			*Settlement->SettlementName);

		return;
	}

	int32 RestoredRoadCount =
		0;

	//-------------------------------------------------------------------------
	// Spawn Saved Road Tiles
	//-------------------------------------------------------------------------

	for (const FTDFRoadSaveData& RoadSaveData :
		SettlementSaveData->Roads)
	{
		if (!RoadSaveData.RoadTag.IsValid())
		{
			continue;
		}

		UTDFRoadDataAsset* RoadData =
			WorldSubsystem->FindRoadByTag(
				RoadSaveData.RoadTag);

		if (!RoadData)
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("Load Restore | Missing RoadData for %s"),
				*RoadSaveData.RoadTag.ToString());

			continue;
		}

		const FTransform RoadTransform(
			FRotator::ZeroRotator,
			RoadSaveData.Location,
			FVector::OneVector);

		ATDFRoadActor* Road =
			GetWorld()->SpawnActorDeferred<ATDFRoadActor>(
				RoadActorClass,
				RoadTransform);

		if (!Road)
		{
			continue;
		}

		Road->InitializeRoad(
			RoadData);

		Road->FinishSpawning(
			RoadTransform);

		Settlement->RegisterRoad(
			Road);

		RestoredRoadCount++;
	}

	//-------------------------------------------------------------------------
	// Final Connection Pass
	//
	// Individual roads refresh neighbors while spawning, but this final pass
	// guarantees every road sees the complete restored road network.
	//-------------------------------------------------------------------------

	for (const TWeakObjectPtr<ATDFRoadActor>& RoadReference :
		Settlement->GetRuntimeRoads())
	{
		ATDFRoadActor* Road =
			RoadReference.Get();

		if (!IsValid(
			Road))
		{
			continue;
		}

		Road->UpdateConnections();
	}

	UE_LOG(
		LogTemp,
		Display,
		TEXT("Load Restore | Settlement: %s | Restored Roads: %d"),
		*Settlement->SettlementName,
		RestoredRoadCount);
}

//-----------------------------------------------------------------------------
// Restore Workplaces
//-----------------------------------------------------------------------------

void ATDFGameMode_Game::RestoreSettlementWorkplaces(
	USettlementDataObject* Settlement,
	const UTDFSaveGame* SaveGame)
{
	if (!Settlement ||
		!SaveGame)
	{
		return;
	}

	const FTDFSettlementSaveData* SettlementSaveData =
		nullptr;

	for (const FTDFSettlementSaveData& Candidate :
		SaveGame->Settlements)
	{
		if (Candidate.SettlementID ==
			Settlement->SettlementID)
		{
			SettlementSaveData =
				&Candidate;

			break;
		}
	}

	if (!SettlementSaveData)
	{
		return;
	}

	UTDFWorkplaceManager* WorkplaceManager =
		Settlement->GetWorkplaceManager();

	if (!WorkplaceManager)
	{
		return;
	}

	for (const FTDFCitizenSaveData& CitizenSaveData :
		SettlementSaveData->Citizens)
	{
		if (!CitizenSaveData.AssignedWorkplaceBuildingID.IsValid())
		{
			continue;
		}

		UCitizenDataObject* Citizen =
			nullptr;

		for (UCitizenDataObject* CandidateCitizen :
			Settlement->Citizens)
		{
			if (!CandidateCitizen)
			{
				continue;
			}

			if (CandidateCitizen->CitizenID ==
				CitizenSaveData.CitizenID)
			{
				Citizen =
					CandidateCitizen;

				break;
			}
		}

		if (!Citizen)
		{
			continue;
		}

		ABuildingActor* Workplace =
			nullptr;

		for (const TWeakObjectPtr<ABuildingActor>& BuildingReference :
			Settlement->GetRuntimeBuildings())
		{
			ABuildingActor* CandidateBuilding =
				BuildingReference.Get();

			if (!IsValid(
				CandidateBuilding))
			{
				continue;
			}

			if (CandidateBuilding->GetBuildingID() ==
				CitizenSaveData.AssignedWorkplaceBuildingID)
			{
				Workplace =
					CandidateBuilding;

				break;
			}
		}

		if (!Workplace)
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("Load Restore | Missing workplace %s for citizen %s %s"),
				*CitizenSaveData.AssignedWorkplaceBuildingID.ToString(),
				*CitizenSaveData.FirstName,
				*CitizenSaveData.LastName);

			continue;
		}

		if (!WorkplaceManager->AssignCitizen(
			Citizen,
			Workplace))
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("Load Restore | Failed workplace assignment | Citizen: %s %s | Building: %s"),
				*CitizenSaveData.FirstName,
				*CitizenSaveData.LastName,
				*CitizenSaveData.AssignedWorkplaceBuildingID.ToString());
		}
	}
}

//-----------------------------------------------------------------------------
// Citizens
//-----------------------------------------------------------------------------

void ATDFGameMode_Game::InitializeSettlementCitizens(
	USettlementDataObject* Settlement,
	bool bLoadedGame,
	ABuildingActor* CitizenSpawnBuilding)
{
	if (!Settlement ||
		!CitizenManagerClass ||
		!GetWorld())
	{
		return;
	}

	ATDFCitizenManager* CitizenManager =
		GetWorld()->SpawnActor<ATDFCitizenManager>(
			CitizenManagerClass);

	if (!CitizenManager)
	{
		return;
	}

	if (bLoadedGame)
	{
		CitizenManager->InitializeLoadedSettlement(
			Settlement);

		if (CitizenSpawnBuilding)
		{
			CitizenManager->SpawnCitizensAt(
				CitizenSpawnBuilding->GetActorLocation());

			UE_LOG(
				LogTemp,
				Display,
				TEXT("Load Restore | Spawned %d citizens for %s"),
				Settlement->Citizens.Num(),
				*Settlement->SettlementName);
		}
		else
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("Load Restore | No citizen spawn anchor for %s; citizens were not spawned"),
				*Settlement->SettlementName);
		}

		return;
	}

	CitizenManager->InitializeNewSettlement(
		Settlement);
}