// Fill out your copyright notice in the Description page of Project Settings.

#include "AchievementManager.h"
#include "AnimalsOfWarCharacter.h"
#include "AnimalsOfWarPlayerController.h"
#include "Engine/World.h"

// Sets default values
AAchievementManager::AAchievementManager()
{
	// Initialize the counter with the number of events
	EventsCounter.Add(EnumEvent::EVENT_HIT_CHARACTER, 0);

	// Initialize array of function pointers
	AchievementBehaviourFunctions[(int)EnumEvent::EVENT_HIT_CHARACTER] = &AAchievementManager::PlayBehaviour_Hit_Character;
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
		IncreaseCounter(Event);
		(this->* (AchievementBehaviourFunctions[(int)Event]))(Entity);
		Unlock(EnumAchievement::ACHIEVEMENT_GOT_CHARACTER_HIT);
		break;
	}
}

void AAchievementManager::IncreaseCounter(EnumEvent Event)
{
	// We need to keep a counter of the number of events that have arrived,
	// in order to unlock the appropiate achievements
	EventsCounter.Add(Event, ++EventsCounter[Event]);
}

void AAchievementManager::Unlock(EnumAchievement AchievementType)
{
	Achievement CurrentAchievement = Achievement(AchievementType, GetWorld());

	// Run the achievement custom behaviour
	CurrentAchievement.RunBehaviour();
}

void AAchievementManager::PlayBehaviour_Hit_Character(UObject * Entity)
{
	AAnimalsOfWarPlayerController* PlayerController = Cast<AAnimalsOfWarPlayerController>(GetWorld()->GetFirstPlayerController());
	AAnimalsOfWarCharacter* PossessedCharacter = Cast<AAnimalsOfWarCharacter>(PlayerController->GetPawn());
	PossessedCharacter->SetGrenadesCounter(+2);
	PossessedCharacter->SetSheepsCounter(+2);
}
