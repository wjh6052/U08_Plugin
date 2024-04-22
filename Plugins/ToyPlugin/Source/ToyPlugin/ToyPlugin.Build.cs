// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ToyPlugin : ModuleRules
{
	public ToyPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateIncludePaths.Add(ModuleDirectory);
			
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
		});
			
		
		PrivateDependencyModuleNames.AddRange(
		new string[]
		{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"EditorStyle",
			"Projects",
			"GameplayDebugger",
			"DesktopPlatform",
			"ProceduralMeshComponent",
			"MainFrame",
			"UnrealEd",
			"Core",
			"Toy"
		});
		
		
	}
}
