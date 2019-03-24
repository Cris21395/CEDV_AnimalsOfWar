// Fill out your copyright notice in the Description page of Project Settings.

#include "Achievement.h"

Achievement::Achievement(EnumAchievement AchievementType)
{
	this->AchievementType = AchievementType;

	switch (AchievementType)
	{
	case EnumAchievement::ACHIEVEMENT_GOT_STREAK_DEATH:
		// TODO: Set description
		break;
	case EnumAchievement::ACHIEVEMENT_GOT_DEATHS_WITHOUT_DAMAGE:
		// TODO: Set description
		break;
	case EnumAchievement::ACHIEVEMENT_GOT_DEATHS_WITHOUT_FAIL:
		// TODO: Set description
		break;
	default:
		break;
	}
}

EnumAchievement Achievement::GetType() const
{
	return AchievementType;
}

const FName & Achievement::GetDescription() const
{
	return Description;
}

void Achievement::RunBehaviour()
{
	// TODO: code bejaviour
}
