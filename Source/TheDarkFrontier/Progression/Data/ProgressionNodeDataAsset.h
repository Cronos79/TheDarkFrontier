// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Progression/Data/ProgressionTypes.h"
#include "ProgressionNodeDataAsset.generated.h"

class UTexture2D;

UCLASS(BlueprintType)
class THEDARKFRONTIER_API UProgressionNodeDataAsset :
	public UDataAsset
{
	GENERATED_BODY()

public:

	//-------------------------------------------------------------------------
	// Identity
	//-------------------------------------------------------------------------

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression")
	FName NodeID;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression")
	FText DisplayName;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression",
		meta = (MultiLine = "true"))
	FText Description;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression")
	TObjectPtr<UTexture2D> Icon;

	//-------------------------------------------------------------------------
	// Graph
	//-------------------------------------------------------------------------

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression|Graph")
	TArray<TObjectPtr<UProgressionNodeDataAsset>>
		PrerequisiteNodes;

	//-------------------------------------------------------------------------
	// Conditions
	//-------------------------------------------------------------------------

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression|Conditions")
	TArray<FProgressionCondition> Conditions;

	//-------------------------------------------------------------------------
	// Rewards
	//-------------------------------------------------------------------------

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression|Rewards")
	TArray<FProgressionReward> Rewards;

	//-------------------------------------------------------------------------
	// Hints
	//-------------------------------------------------------------------------

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression|Hints",
		meta = (MultiLine = "true"))
	FText HintText;

	//-------------------------------------------------------------------------
	// UI
	//-------------------------------------------------------------------------

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Progression|UI")
	FVector2D TreePosition =
		FVector2D::ZeroVector;
};