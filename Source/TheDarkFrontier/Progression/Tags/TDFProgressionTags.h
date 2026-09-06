// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace TDFProgressionTags
{
	//-------------------------------------------------------------------------
	// Metrics
	//-------------------------------------------------------------------------

	THEDARKFRONTIER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Metric_Building_Placed);

	THEDARKFRONTIER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Metric_Building_Completed);

	THEDARKFRONTIER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Metric_Resource_Gathered);

	THEDARKFRONTIER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Metric_Tree_Cut);

	THEDARKFRONTIER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Metric_Enemy_Killed);

	THEDARKFRONTIER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Metric_Population);

	//-------------------------------------------------------------------------
	// Rewards
	//-------------------------------------------------------------------------

	THEDARKFRONTIER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Reward_Unlock_Building);

	THEDARKFRONTIER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Reward_Unlock_Road);

	THEDARKFRONTIER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Reward_Unlock_Resource);

	THEDARKFRONTIER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Reward_Unlock_Skill);

	THEDARKFRONTIER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Reward_Unlock_Recipe);

	THEDARKFRONTIER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Reward_Unlock_Upgrade);
}