// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GHCombatPrototype : ModuleRules
{
	public GHCombatPrototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"GHCombatPrototype",
			"GHCombatPrototype/Variant_Platforming",
			"GHCombatPrototype/Variant_Platforming/Animation",
			"GHCombatPrototype/Variant_Combat",
			"GHCombatPrototype/Variant_Combat/AI",
			"GHCombatPrototype/Variant_Combat/Animation",
			"GHCombatPrototype/Variant_Combat/Gameplay",
			"GHCombatPrototype/Variant_Combat/Interfaces",
			"GHCombatPrototype/Variant_Combat/UI",
			"GHCombatPrototype/Variant_SideScrolling",
			"GHCombatPrototype/Variant_SideScrolling/AI",
			"GHCombatPrototype/Variant_SideScrolling/Gameplay",
			"GHCombatPrototype/Variant_SideScrolling/Interfaces",
			"GHCombatPrototype/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
