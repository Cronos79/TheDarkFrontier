// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#include "Settlements/Data/SettlementDataObject.h"

#include "Buildings/Actors/BuildingActor.h"
#include "Buildings/Data/BuildingDataAsset.h"
#include "Jobs/Systems/TDFJobManager.h"
#include "Resources/Actors/TDFSalvagePileActor.h"
#include "Resources/Inventory/TDFInventory.h"
#include "Core/TDFGameMode_Game.h"

bool USettlementDataObject::RemoveBuilding(
	ABuildingActor* Building)
{
	if (!IsValid(
		Building))
	{
		return false;
	}

	UWorld* World =
		Building->GetWorld();

	if (!World)
	{
		return false;
	}

	//-------------------------------------------------------------------------
	// Building State
	//-------------------------------------------------------------------------

	const ETDFBuildingVisualState VisualState =
		Building->GetVisualState();

	UBuildingDataAsset* BuildingData =
		Building->GetBuildingData();

	//-------------------------------------------------------------------------
	// Salvage
	//-------------------------------------------------------------------------

	TArray<FTDFResourceStack>
		SalvageResources;

	//-------------------------------------------------------------------------
	// Add / Merge Salvage Resource
	//-------------------------------------------------------------------------

	auto AddSalvageResource =
		[&SalvageResources](
			FGameplayTag ResourceTag,
			int32 Amount)
		{
			if (!ResourceTag.IsValid() ||
				Amount <= 0)
			{
				return;
			}

			for (FTDFResourceStack& ExistingStack :
				SalvageResources)
			{
				if (ExistingStack.ResourceTag !=
					ResourceTag)
				{
					continue;
				}

				ExistingStack.Amount +=
					Amount;

				return;
			}

			FTDFResourceStack NewStack;

			NewStack.ResourceTag =
				ResourceTag;

			NewStack.Amount =
				Amount;

			SalvageResources.Add(
				NewStack);
		};

	//-------------------------------------------------------------------------
	// Construction Cancellation
	//
	// Return only resources that have actually been delivered to the
	// construction site.
	//-------------------------------------------------------------------------

	if (VisualState ==
		ETDFBuildingVisualState::Construction)
	{
		UTDFInventory* ConstructionInventory =
			Building->GetConstructionInventory();

		if (ConstructionInventory)
		{
			for (const FTDFResourceStack& Stack :
				ConstructionInventory->GetItems())
			{
				AddSalvageResource(
					Stack.ResourceTag,
					Stack.Amount);
			}
		}
	}

	//-------------------------------------------------------------------------
	// Completed Building Demolition
	//
	// Return:
	//
	// 1. 100% of resources currently stored inside the building.
	// 2. 50% of the original construction materials.
	//-------------------------------------------------------------------------

	else if (VisualState ==
		ETDFBuildingVisualState::Permanent)
	{
		//---------------------------------------------------------------------
		// Building Inventory
		//---------------------------------------------------------------------

		UTDFInventory* BuildingInventory =
			Building->GetInventory();

		if (BuildingInventory)
		{
			for (const FTDFResourceStack& Stack :
				BuildingInventory->GetItems())
			{
				AddSalvageResource(
					Stack.ResourceTag,
					Stack.Amount);
			}
		}

		//---------------------------------------------------------------------
		// Construction Material Salvage
		//---------------------------------------------------------------------

		if (BuildingData)
		{
			for (const FTDFResourceStack& CostStack :
				BuildingData->ConstructionCost)
			{
				if (!CostStack.ResourceTag.IsValid() ||
					CostStack.Amount <= 0)
				{
					continue;
				}

				// 50% salvage.
				//
				// Integer division intentionally rounds odd amounts down.
				//
				// Examples:
				// 10 -> 5
				//  5 -> 2
				//  1 -> 0

				const int32 SalvageAmount =
					CostStack.Amount /
					2;

				AddSalvageResource(
					CostStack.ResourceTag,
					SalvageAmount);
			}
		}
	}

	//-------------------------------------------------------------------------
	// Validate Salvage Configuration
	//
	// If resources must be preserved, do not destroy the building unless a
	// salvage pile can actually be spawned.
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
					"Building Removal | Cannot remove %s | Salvage resources exist but SalvagePileActorClass is not configured."),
				*Building->GetName());

			return false;
		}

		SalvagePileClass =
			GameMode->SalvagePileActorClass;
	}

	//-------------------------------------------------------------------------
	// Cancel Runtime Jobs
	//-------------------------------------------------------------------------

	if (JobManager)
	{
		JobManager->ClearJobsReferencingBuilding(
			Building);
	}

	//-------------------------------------------------------------------------
	// Spawn Salvage
	//-------------------------------------------------------------------------

	if (!SalvageResources.IsEmpty())
	{
		const FTransform SalvageTransform(
			Building->GetActorRotation(),
			Building->GetActorLocation(),
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
					"Building Removal | Failed to spawn salvage pile for %s."),
				*Building->GetName());

			return false;
		}

		SalvagePile->InitializeSalvage(
			SalvageResources);

		UE_LOG(
			LogTemp,
			Display,
			TEXT(
				"Building Removal | Spawned salvage pile for %s with %d resource stack(s)."),
			*Building->GetName(),
			SalvageResources.Num());
	}

	//-------------------------------------------------------------------------
	// Remove Settlement Runtime State
	//-------------------------------------------------------------------------

	UnregisterBuilding(
		Building);

	//-------------------------------------------------------------------------
	// Destroy World Actor
	//-------------------------------------------------------------------------

	const FString BuildingName =
		Building->GetName();

	const bool bDestroyed =
		Building->Destroy();

	if (!bDestroyed)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT(
				"Building Removal | Failed to destroy building %s."),
			*BuildingName);

		return false;
	}

	UE_LOG(
		LogTemp,
		Display,
		TEXT(
			"Building Removal | Removed building %s."),
		*BuildingName);

	return true;
}