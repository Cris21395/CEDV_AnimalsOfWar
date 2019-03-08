// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CEDV_HansAtWarEditorTarget : TargetRules
{
	public CEDV_HansAtWarEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "CEDV_HansAtWar" } );
	}
}
