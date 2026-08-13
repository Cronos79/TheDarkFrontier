// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDFGameMode_Game.generated.h"

/**
 * 
 */
UCLASS()
class THEDARKFRONTIER_API ATDFGameMode_Game : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
	
	
};
