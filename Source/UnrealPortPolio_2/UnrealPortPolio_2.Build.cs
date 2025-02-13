// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealPortPolio_2 : ModuleRules
{
	public UnrealPortPolio_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(ModuleDirectory);

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "AIModule",
            "GameplayTasks","Niagara","NavigationSystem","EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "GameplayAbilities", "GameplayTags", "GameplayTasks", "Niagara", "CableComponent" });

     

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
