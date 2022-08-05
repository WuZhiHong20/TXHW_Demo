// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HW : ModuleRules
{
	public HW(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" , "UMG", "AIModule","GameplayTasks"});

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
