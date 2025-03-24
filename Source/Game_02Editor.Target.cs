// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Game_02EditorTarget : TargetRules
{
	public Game_02EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

        ExtraModuleNames.AddRange( new string[] { "Game_02" } );
	}
}
