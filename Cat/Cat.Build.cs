// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cat : ModuleRules
{
	public Cat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", 
			"HeadMountedDisplay", "EnhancedInput", "UMG", "Slate", "SlateCore" });
	}
}
