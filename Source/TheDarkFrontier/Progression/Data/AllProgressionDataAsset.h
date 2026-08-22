// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Progression/Data/ProgressionTypes.h"
#include "AllProgressionDataAsset.generated.h"

class UProgressionNodeDataAsset;

UCLASS(BlueprintType)
class THEDARKFRONTIER_API UAllProgressionDataAsset :
	public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression")
	FText DisplayName;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression")
	TArray<TObjectPtr<UProgressionNodeDataAsset>>
		Nodes;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression|Starting")
	TArray<FProgressionReward>
		StartingRewards;
};