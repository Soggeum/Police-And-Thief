// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DedicatedX : ModuleRules
{
	public DedicatedX(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
            // UI
			"UMG",
            "AIModule",
            "NavigationSystem",
            "GameplayTasks",
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        PublicIncludePaths.AddRange(new string[]
        {
            "DedicatedX", // 이게 없으면 헤더파일 인클루드시 경로를 찾지 못함.
		});
    }
}
