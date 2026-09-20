// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#include "Jobs/Systems/TDFJobManager.h"

#include "Buildings/Actors/BuildingActor.h"
#include "Citizens/Data/CitizenDataObject.h"
#include "Jobs/Types/TDFJobTypes.h"
#include "Settlements/Data/SettlementDataObject.h"

void UTDFJobManager::ClearJobsReferencingBuilding(
	ABuildingActor* Building)
{
	if (!SettlementData ||
		!IsValid(
			Building))
	{
		return;
	}

	int32 ClearedJobCount =
		0;

	for (UCitizenDataObject* Citizen :
		SettlementData->Citizens)
	{
		if (!Citizen)
		{
			continue;
		}

		const FTDFJobAssignment& Assignment =
			Citizen->GetCurrentJobAssignment();

		const bool bReferencesBuilding =
			Assignment.SourceActor.Get() ==
				Building ||
			Assignment.TargetBuilding.Get() ==
				Building ||
			Assignment.WorkTargetActor.Get() ==
				Building;

		if (!bReferencesBuilding)
		{
			continue;
		}

		ClearCurrentJob(
			Citizen);

		++ClearedJobCount;
	}

	UE_LOG(
		LogTemp,
		Display,
		TEXT(
			"Jobs | Cleared %d current job(s) referencing building %s."),
		ClearedJobCount,
		*Building->GetName());
}