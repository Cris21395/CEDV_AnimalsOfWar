// Fill out your copyright notice in the Description page of Project Settings.

#include "AchievementManager.h"

// Sets default values
AAchievementManager::AAchievementManager()
{
	// Initialize the counter with the number of events
	EventsCounter.Add(EnumEvent::EVENT_HIT_CHARACTER, 1);
}

// Called when the game starts or when spawned
void AAchievementManager::BeginPlay()
{
	// Bind delegate to OnNotify function
	OnNotifyDelegate.BindUObject(this, &AAchievementManager::OnNotify);
}

void AAchievementManager::OnNotify(UObject * Entity, EnumEvent Event)
{
	switch (Event) 
	{
	case EnumEvent::EVENT_HIT_CHARACTER:
		if (EventsCounter[Event] >= 0)
		{
			DecreaseCounter(Event);
			Unlock(EnumAchievement::ACHIEVEMENT_GOT_FIRST_DEATH);
		}
		break;
	}
}

void AAchievementManager::DecreaseCounter(EnumEvent Event)
{
	// We need to keep a counter of the number of events that have arrived,
	// in order to unlock the appropiate achievements
	EventsCounter.Add(Event, --EventsCounter[Event]);
}

void AAchievementManager::Unlock(EnumAchievement AchievementType)
{
	Achievement CurrentAchievement = Achievement(AchievementType, GetWorld());

	// Run the achievement custom behaviour
	CurrentAchievement.RunBehaviour();
}
