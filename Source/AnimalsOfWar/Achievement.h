// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EnumAchievement : uint8;

/**
 * Generic Achievement class to create custom achievements
 */
class ANIMALSOFWAR_API Achievement
{
public:
	Achievement(EnumAchievement AchievementType, TWeakObjectPtr<UWorld> World);

	EnumAchievement GetType() const;
	const FName& GetDescription() const;

	// This method could be overriden in child classes
	// to implement the custom behaviour of the concrete
	// achievement
	void RunBehaviour();

private:
	TWeakObjectPtr<UWorld> World;

	FName Description;
	EnumAchievement AchievementType;
};

enum class EnumAchievement : uint8
{
	ACHIEVEMENT_GOT_FIRST_DEATH,
	ACHIEVEMENT_GOT_STREAK_DEATH,
	ACHIEVEMENT_GOT_DEATHS_WITHOUT_FAIL,
	ACHIEVEMENT_GOT_DEATHS_WITHOUT_DAMAGE
};