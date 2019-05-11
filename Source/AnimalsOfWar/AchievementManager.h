// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Achievement.h"
#include "GameFramework/Actor.h"
#include "AchievementManager.generated.h"

enum class EnumEvent : uint8
{
	EVENT_HIT_CHARACTER,
	EVENT_ALL_CHARACTERS_DEAD,

	LAST_EVENT  // Retrieve the number of events
};

DECLARE_DELEGATE_TwoParams(FAchievementManagerDelegate, class UObject*, enum class EnumEvent);

/**
 * AchievementManager class used to handle all achievements of the game
 */
UCLASS()
class ANIMALSOFWAR_API AAchievementManager : public AActor
{
	GENERATED_BODY()
	
public:
	AAchievementManager();

	FAchievementManagerDelegate OnNotifyDelegate;

public:
	void OnNotify(UObject* Entity, EnumEvent Event);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// The Function Pointer Variable Type
	// Functions take in 0 parameters and return void
	typedef void (AAchievementManager::*FunctionPtrType)(UObject*);

	// Array of Function Pointers
	FunctionPtrType AchievementBehaviourFunctions[(int)EnumEvent::LAST_EVENT];

	void IncreaseCounter(EnumEvent Event);
	void Unlock(EnumAchievement AchievementType);

	void PlayBehaviour_Hit_Character(UObject * Entity);

private:
	TMap<EnumEvent, uint32> EventsCounter;
};
