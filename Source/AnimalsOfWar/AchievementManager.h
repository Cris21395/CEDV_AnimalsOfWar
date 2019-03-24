// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Observer.h"
#include "Achievement.h"
#include "GameFramework/Actor.h"
#include "AchievementManager.generated.h"

UCLASS()
class ANIMALSOFWAR_API AAchievementManager : public AActor, public IObserver
{
	GENERATED_BODY()
	
public:
	AAchievementManager();

	UFUNCTION(BlueprintCallable, Category = "Observer Pattern")
		void OnNotify(UObject* Entity, EEvent Event);

public:

private:
	void IncreaseCounter(EEvent Event);
	void Unlock(EnumAchievement AchievementType);

private:
	TMap<EEvent, uint32> EventsCounter;
	TMap<EnumAchievement, Achievement> Achievements;
};
