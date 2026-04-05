// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameProject : ModuleRules
{
	public GameProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate",
            "GameplayAbilities",      // Ìí¼Ó GAS Ö÷Ä£¿é
            "GameplayTags",           // GAS ÒÀÀµ
            "GameplayTasks"           // GAS ÒÀÀµ
		});

		PrivateDependencyModuleNames.AddRange(new string[] {});

		PublicIncludePaths.AddRange(new string[] {
			"GameProject",
			"GameProject/Variant_Strategy",
			"GameProject/Variant_Strategy/UI",
			"GameProject/Variant_TwinStick",
			"GameProject/Variant_TwinStick/AI",
			"GameProject/Variant_TwinStick/Gameplay",
			"GameProject/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
