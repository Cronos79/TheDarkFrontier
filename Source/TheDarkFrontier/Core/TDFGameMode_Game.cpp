// Fill out your copyright notice in the Description page of Project Settings.


#include "TDFGameMode_Game.h"
#include "World/Systems/TDFTimeSubsystem.h"

void ATDFGameMode_Game::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* GameInstance =
		GetGameInstance();

	if (!GameInstance)
	{
		return;
	}

	UTDFTimeSubsystem* TimeSubsystem =
		GameInstance->GetSubsystem<UTDFTimeSubsystem>();

	if (!TimeSubsystem)
	{
		return;
	}

	TimeSubsystem->StartTime();
}