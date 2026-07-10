// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "BuildingTypes.generated.h"

UENUM(BlueprintType)
enum class EBuildingState : uint8
{
	Placement,
	Construction,
	Finished
};

USTRUCT(BlueprintType)
struct FBuildingStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value = 0;
};