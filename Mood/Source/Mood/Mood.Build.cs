// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Mood : ModuleRules
{
	public Mood(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"AIModule", "Core", "CoreUObject", 
			"Engine", "InputCore", "EnhancedInput", 
			"UMG", "AdvancedWidgets", "Niagara",
		});
	}
}
