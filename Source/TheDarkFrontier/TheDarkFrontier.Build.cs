// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class TheDarkFrontier : ModuleRules
{
	public TheDarkFrontier(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "EnhancedInput",
                "MoviePlayer",
                "UMG",
                "SunPosition",
                "Landscape",
                "GameplayTags"
            });

        PrivateDependencyModuleNames.AddRange(new string[]
            {
                "Slate",
                "SlateCore"
            });

        PublicIncludePaths.Add(ModuleDirectory);

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
