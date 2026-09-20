// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#include "Settlements/Data/SettlementDataObject.h"

#include "Buildings/Actors/BuildingActor.h"
#include "Buildings/Data/BuildingDataAsset.h"
#include "Buildings/Tags/TDFBuildingTags.h"
#include "Jobs/Systems/TDFJobManager.h"
#include "Resources/Actors/TDFSalvagePileActor.h"
#include "Resources/Inventory/TDFInventory.h"
#include "Core/TDFGameMode_Game.h"

bool USettlementDataObject::RetireStartingWagon()
{
	ABuildingActor* Wagon =
		nullptr;

	//-------------------------------------------------------------------------
	// Find Starting Wagon
	//-------------------------------------------------------------------------

	for (const TWeakObjectPtr<ABuildingActor>& BuildingReference :
		RuntimeBuildings)
	{
		ABuildingActor* Building =
			BuildingReference.Get();

		if (!IsValid(
			Building))
		{
			continue;
		}

		UBuildingDataAsset* BuildingData =
			Building->GetBuildingData();

		if (!BuildingData ||
			BuildingData->BuildingTag !=
				TDFBuildingTags::Building_Civic_Wagon)
		{
			continue;
		}

		Wagon =
			Building;

		break;
	}

	//-------------------------------------------------------------------------
	// Wagon Already Gone
	//-------------------------------------------------------------------------

	if (!IsValid(
		Wagon))
	{
		return true;
	}

	UWorld* World =
		Wagon->GetWorld();

	if (!World)
	{
		return false;
	}

	//-------------------------------------------------------------------------
	// Capture Wagon Inventory
	//
	// Wagon retirement returns 100% of whatever resources are still inside
	// the wagon. It does NOT receive normal building-demolition salvage.
	//-------------------------------------------------------------------------

	TArray<FTDFResourceStack>
		SalvageResources;

	UTDFInventory* WagonInventory =
		Wagon->GetInventory();

	if (WagonInventory)
	{
		for (const FTDFResourceStack& Stack :
			WagonInventory->GetItems())
		{
			if (!Stack.ResourceTag.IsValid() ||
				Stack.Amount <= 0)
			{
				continue;
			}

			SalvageResources.Add(
				Stack);
		}
	}

	//-------------------------------------------------------------------------
	// Validate Salvage Configuration
	//-------------------------------------------------------------------------

	TSubclassOf<ATDFSalvagePileActor>
		SalvagePileClass;

	if (!SalvageResources.IsEmpty())
	{
		ATDFGameMode_Game* GameMode =
			World->GetAuthGameMode<
				ATDFGameMode_Game>();

		if (!GameMode ||
			!GameMode->SalvagePileActorClass)
		{
			UE_LOG(
				LogTemp,
				Error,
				TEXT(
					"Wagon Retirement | Cannot retire wagon | SalvagePileActorClass is not configured."));

			return false;
		}

		SalvagePileClass =
			GameMode->SalvagePileActorClass;
	}

	//-------------------------------------------------------------------------
	// Clear Jobs Referencing Wagon
	//
	// This catches citizens hauling from the wagon or otherwise currently
	// holding a job assignment that references it.
	//-------------------------------------------------------------------------

	if (JobManager)
	{
		JobManager->ClearJobsReferencingBuilding(
			Wagon);
	}

	//-------------------------------------------------------------------------
	// Spawn Salvage Pile
	//-------------------------------------------------------------------------

	if (!SalvageResources.IsEmpty())
	{
		const FTransform SalvageTransform(
			Wagon->GetActorRotation(),
			Wagon->GetActorLocation(),
			FVector::OneVector);

		ATDFSalvagePileActor* SalvagePile =
			World->SpawnActor<
				ATDFSalvagePileActor>(
					SalvagePileClass,
					SalvageTransform);

		if (!IsValid(
			SalvagePile))
		{
			UE_LOG(
				LogTemp,
				Error,
				TEXT(
					"Wagon Retirement | Failed to spawn salvage pile."));

			return false;
		}

		SalvagePile->InitializeSalvage(
			SalvageResources);
	}

	//-------------------------------------------------------------------------
	// Remove Wagon From Settlement
	//-------------------------------------------------------------------------

	UnregisterBuilding(
		Wagon);

	//-------------------------------------------------------------------------
	// Destroy Wagon
	//-------------------------------------------------------------------------

	const FString WagonName =
		Wagon->GetName();

	if (!Wagon->Destroy())
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT(
				"Wagon Retirement | Failed to destroy %s."),
			*WagonName);

		return false;
	}

	UE_LOG(
		LogTemp,
		Display,
		TEXT(
			"Wagon Retirement | %s retired | Salvage stacks: %d"),
		*WagonName,
		SalvageResources.Num());

	return true;
}