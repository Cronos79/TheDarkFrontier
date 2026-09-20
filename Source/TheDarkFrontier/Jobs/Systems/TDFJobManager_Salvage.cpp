// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#include "Jobs/Systems/TDFJobManager.h"

#include "Buildings/Actors/BuildingActor.h"
#include "Buildings/Data/BuildingDataAsset.h"
#include "Buildings/Tags/TDFBuildingTags.h"
#include "Citizens/Data/CitizenDataObject.h"
#include "EngineUtils.h"
#include "Jobs/Tags/TDFJobTags.h"
#include "Jobs/Types/TDFJobTypes.h"
#include "Resources/Actors/TDFSalvagePileActor.h"
#include "Resources/Inventory/TDFInventory.h"
#include "Settlements/Data/SettlementDataObject.h"

//-----------------------------------------------------------------------------
// Salvage Hauling Demand
//-----------------------------------------------------------------------------

bool UTDFJobManager::TryAssignSalvageHaulingDemand(
	UCitizenDataObject* Citizen)
{
	if (!SettlementData ||
		!Citizen ||
		!GetWorld())
	{
		return false;
	}

	for (TActorIterator<ATDFSalvagePileActor> It(
		GetWorld());
		It;
		++It)
	{
		ATDFSalvagePileActor* SalvagePile =
			*It;

		if (!IsValid(
			SalvagePile) ||
			SalvagePile->IsEmpty())
		{
			continue;
		}

		UTDFInventory* SalvageInventory =
			SalvagePile->GetInventory();

		if (!SalvageInventory)
		{
			continue;
		}

		for (const FTDFResourceStack& Stack :
			SalvageInventory->GetItems())
		{
			if (!Stack.ResourceTag.IsValid() ||
				Stack.Amount <= 0)
			{
				continue;
			}

			//-----------------------------------------------------------------
			// Account For Other Citizens Already Heading To This Pile
			//-----------------------------------------------------------------

			const int32 ReservedAmount =
				GetReservedAmountFromSalvagePile(
					SalvagePile,
					Stack.ResourceTag);

			const int32 AvailableAmount =
				Stack.Amount -
				ReservedAmount;

			if (AvailableAmount <= 0)
			{
				continue;
			}

			//-----------------------------------------------------------------
			// Preferred Destination - Normal Storage
			//
			// Warehouse and future normal-storage buildings remain the
			// preferred destination for salvage.
			//-----------------------------------------------------------------

			ABuildingActor* StorageBuilding =
				FindStorageBuildingForResource(
					Stack.ResourceTag,
					nullptr);

			//-----------------------------------------------------------------
			// Salvage-Only Fallback - Expedition Wagon
			//
			// The wagon is NOT general settlement storage.
			//
			// Gathering buildings, production buildings and other ordinary
			// hauling paths continue to ignore it.
			//
			// Only salvage recovery may return resources to the wagon.
			//-----------------------------------------------------------------

			if (!StorageBuilding)
			{
				const TArray<TWeakObjectPtr<ABuildingActor>>& Buildings =
					SettlementData->GetRuntimeBuildings();

				for (const TWeakObjectPtr<ABuildingActor>& BuildingReference :
					Buildings)
				{
					ABuildingActor* CandidateBuilding =
						BuildingReference.Get();

					if (!IsValid(
						CandidateBuilding))
					{
						continue;
					}

					if (CandidateBuilding->GetVisualState() !=
						ETDFBuildingVisualState::Permanent)
					{
						continue;
					}

					UBuildingDataAsset* BuildingData =
						CandidateBuilding->GetBuildingData();

					if (!BuildingData ||
						BuildingData->BuildingTag !=
						TDFBuildingTags::Building_Civic_Wagon)
					{
						continue;
					}

					UTDFInventory* WagonInventory =
						CandidateBuilding->GetInventory();

					if (!WagonInventory)
					{
						continue;
					}

					if (!WagonInventory->CanAddResource(
						Stack.ResourceTag,
						1))
					{
						continue;
					}

					StorageBuilding =
						CandidateBuilding;

					break;
				}
			}

			if (!StorageBuilding)
			{
				continue;
			}

			//-----------------------------------------------------------------
			// Assign Salvage Transfer
			//-----------------------------------------------------------------

			if (AssignSalvageHaulingTransfer(
				Citizen,
				SalvagePile,
				StorageBuilding,
				Stack.ResourceTag,
				AvailableAmount))
			{
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
// Assign Salvage Pile -> Storage Hauling Transfer
//-----------------------------------------------------------------------------

bool UTDFJobManager::AssignSalvageHaulingTransfer(
	UCitizenDataObject* Citizen,
	ATDFSalvagePileActor* SalvagePile,
	ABuildingActor* TargetBuilding,
	FGameplayTag ResourceTag,
	int32 RequestedAmount)
{
	if (!Citizen ||
		!IsValid(
			SalvagePile) ||
		!IsValid(
			TargetBuilding) ||
		!ResourceTag.IsValid() ||
		RequestedAmount <= 0)
	{
		return false;
	}

	UTDFInventory* CitizenInventory =
		Citizen->GetInventory();

	UTDFInventory* SourceInventory =
		SalvagePile->GetInventory();

	UTDFInventory* TargetInventory =
		TargetBuilding->GetInventory();

	if (!CitizenInventory ||
		!SourceInventory ||
		!TargetInventory)
	{
		return false;
	}

	//-------------------------------------------------------------------------
	// Available Salvage
	//-------------------------------------------------------------------------

	int32 CarryAmount =
		FMath::Min(
			RequestedAmount,
			SourceInventory->GetAmount(
				ResourceTag));

	while (CarryAmount > 0)
	{
		if (CitizenInventory->CanAddResource(
			ResourceTag,
			CarryAmount) &&
			TargetInventory->CanAddResource(
				ResourceTag,
				CarryAmount))
		{
			break;
		}

		--CarryAmount;
	}

	if (CarryAmount <= 0)
	{
		return false;
	}

	//-------------------------------------------------------------------------
	// Job Assignment
	//-------------------------------------------------------------------------

	FTDFJobAssignment Assignment;

	Assignment.SourceActor =
		SalvagePile;

	Assignment.TargetBuilding =
		TargetBuilding;

	Assignment.ResourceTag =
		ResourceTag;

	Assignment.Amount =
		CarryAmount;

	Assignment.HaulingSourceInventory =
		ETDFHaulingSourceInventory::SalvagePile;

	Assignment.HaulingTargetInventory =
		ETDFHaulingTargetInventory::Building;

	Citizen->SetCurrentJobAssignment(
		Assignment);

	Citizen->SetCurrentJobTag(
		TDFJobTags::Job_Unassigned_Hauling);

	return true;
}

//-----------------------------------------------------------------------------
// Reservation - Salvage Source
//-----------------------------------------------------------------------------

int32 UTDFJobManager::GetReservedAmountFromSalvagePile(
	ATDFSalvagePileActor* SalvagePile,
	FGameplayTag ResourceTag) const
{
	if (!SettlementData ||
		!IsValid(
			SalvagePile) ||
		!ResourceTag.IsValid())
	{
		return 0;
	}

	int32 ReservedAmount =
		0;

	for (UCitizenDataObject* Citizen :
		SettlementData->Citizens)
	{
		if (!Citizen)
		{
			continue;
		}

		if (Citizen->GetCurrentJobTag() !=
			TDFJobTags::Job_Unassigned_Hauling)
		{
			continue;
		}

		const FTDFJobAssignment& Assignment =
			Citizen->GetCurrentJobAssignment();

		if (Assignment.HaulingSourceInventory !=
			ETDFHaulingSourceInventory::SalvagePile)
		{
			continue;
		}

		if (Assignment.SourceActor.Get() !=
			SalvagePile ||
			Assignment.ResourceTag !=
			ResourceTag ||
			Assignment.Amount <= 0)
		{
			continue;
		}

		ReservedAmount +=
			Assignment.Amount;
	}

	return ReservedAmount;
}