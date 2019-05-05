// Fill out your copyright notice in the Description page of Project Settings.

#include "Achievement.h"
#include "AnimalsOfWarHUD.h"
#include "AnimalsOfWarPlayerController.h"
#include "Blueprint/UserWidget.h"

Achievement::Achievement(EnumAchievement AchievementType, TWeakObjectPtr<UWorld> World)
{
	this->AchievementType = AchievementType;
	this->World = World;

	switch (AchievementType)
	{
	case EnumAchievement::ACHIEVEMENT_GOT_FIRST_DEATH:
		this->Description = TEXT("Got first death!");
		break;
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
	// Call the Blueprint function "Unlock_Achievement" from HUD
	if (World.IsValid())
	{
		AAnimalsOfWarPlayerController* Player = Cast<AAnimalsOfWarPlayerController>(World->GetFirstPlayerController());
		if (Player)
		{
			AAnimalsOfWarHUD* HUD = Cast<AAnimalsOfWarHUD>(Player->GetHUD());
			if (HUD)
			{
				// Get reference of HUD widget
				UUserWidget* HUDWidget = HUD->pHUDWidget.Get();
				if (HUDWidget)
				{
					// Get the function as named in Blueprint
					UFunction* UnlockAchievementFunction = HUDWidget->FindFunction(TEXT("Unlock_Achievement"));
					if (UnlockAchievementFunction) 
					{
						// Once we got the function, invoke it. Input parameters have to be provided
						// in a struct, in the same order they are defined in the Blueprint function.
						// In case the function has a return value, it will be specified as the last
						// member in the struct.
						HUDWidget->ProcessEvent(UnlockAchievementFunction, { &Description });
					}
				}
			}
		}
	}
}
