// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CEDV_HansAtWarTarget : TargetRules
{
	public CEDV_HansAtWarTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "CEDV_HansAtWar" } );
	}
}
