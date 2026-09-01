// Copyright © 2026 The Dark Frontier Project. All Rights Reserved.

#include "Progression/Tags/TDFProgressionTags.h"

namespace TDFProgressionTags
{
	//-------------------------------------------------------------------------
	// Metrics
	//-------------------------------------------------------------------------

	UE_DEFINE_GAMEPLAY_TAG(
		Metric_Building_Placed,
		"Progression.Metric.Building.Placed");

	UE_DEFINE_GAMEPLAY_TAG(
		Metric_Building_Completed,
		"Progression.Metric.Building.Completed");

	UE_DEFINE_GAMEPLAY_TAG(
		Metric_Resource_Gathered,
		"Progression.Metric.Resource.Gathered");

	UE_DEFINE_GAMEPLAY_TAG(
		Metric_Tree_Cut,
		"Progression.Metric.Tree.Cut");

	UE_DEFINE_GAMEPLAY_TAG(
		Metric_Enemy_Killed,
		"Progression.Metric.Enemy.Killed");

	UE_DEFINE_GAMEPLAY_TAG(
		Metric_Population,
		"Progression.Metric.Population");

	//-------------------------------------------------------------------------
	// Rewards
	//-------------------------------------------------------------------------

	UE_DEFINE_GAMEPLAY_TAG(
		Reward_Unlock_Building,
		"Progression.Reward.Unlock.Building");

	UE_DEFINE_GAMEPLAY_TAG(
		Reward_Unlock_Resource,
		"Progression.Reward.Unlock.Resource");

	UE_DEFINE_GAMEPLAY_TAG(
		Reward_Unlock_Skill,
		"Progression.Reward.Unlock.Skill");

	UE_DEFINE_GAMEPLAY_TAG(
		Reward_Unlock_Recipe,
		"Progression.Reward.Unlock.Recipe");

	UE_DEFINE_GAMEPLAY_TAG(
		Reward_Unlock_Upgrade,
		"Progression.Reward.Unlock.Upgrade");
}