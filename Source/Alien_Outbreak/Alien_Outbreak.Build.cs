// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Alien_Outbreak : ModuleRules
{
	public Alien_Outbreak(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
