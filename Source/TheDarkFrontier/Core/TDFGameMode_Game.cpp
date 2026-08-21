// Fill out your copyright notice in the Description page of Project Settings.

#include "TDFGameMode_Game.h"

#include "Citizens/Systems/TDFCitizenManager.h"
#include "Progression/Data/ProgressionTreeDataAsset.h"
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
	// Time
	//-------------------------------------------------------------------------

	UTDFTimeSubsystem* TimeSubsystem =
		GameInstance->GetSubsystem<UTDFTimeSubsystem>();

	if (TimeSubsystem)
	{
		TimeSubsystem->StartTime();
	}

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

	if (AllResources)
	{
		WorldSubsystem->SetAllResources(
			AllResources);
	}

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

		if (SettlementProgression)
		{
			Settlement->InitializeProgression(
				SettlementProgression);
		}

		if (!CitizenManagerClass)
		{
			continue;
		}

		ATDFCitizenManager* CitizenManager =
			GetWorld()->SpawnActor<ATDFCitizenManager>(
				CitizenManagerClass);

		if (!CitizenManager)
		{
			continue;
		}

		CitizenManager->InitializeSettlement(
			Settlement);
	}
}