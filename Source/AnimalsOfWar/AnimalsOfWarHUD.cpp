// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarHUD.h"
#include "AnimalsOfWarCharacter.h"
#include "AnimalsOfWarManager.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"
#include "ProgressBar.h"
#include "Image.h"
#include "EngineUtils.h"
#include "Engine.h"
#include "Blueprint/UserWidget.h"

AAnimalsOfWarHUD::AAnimalsOfWarHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDWidgetObject (TEXT("/Game/Blueprints/UI/BP_HUDCharacter"));

	// Save pointer to widgets
	if (HUDWidgetObject.Class) 
	{
		pHUDWidgetClass = HUDWidgetObject.Class;
	}
}

void AAnimalsOfWarHUD::BeginPlay() 
{
	Super::BeginPlay();

	if (pHUDWidgetClass) // Add widget to viewport and get references
	{
		// Create widget and save it in the pointer
		pHUDWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), pHUDWidgetClass);

		if (pHUDWidget.IsValid()) 
		{
			pHUDWidget->AddToViewport();

			// Retrieve TextBlock widgets
			pNumGrenadesText = (UTextBlock*)pHUDWidget->GetWidgetFromName("NumGrenades");
			pNumSheepsText = (UTextBlock*)pHUDWidget->GetWidgetFromName("NumSheeps");
			pCounterText = (UTextBlock*)pHUDWidget->GetWidgetFromName("TimeCounter");
			pAimImage = (UImage*)pHUDWidget->GetWidgetFromName("AimImage");

			
			// Binding the progress bars to the health of the characters
			AAnimalsOfWarManager* Manager = nullptr;
			for (TActorIterator<AAnimalsOfWarManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				// Conversion to smart pointer
				Manager = *ActorItr;
			}
			for (int i = 0; i < Manager->Player1Characters.Num(); i++) 
			{	
				UProgressBar* allie_health = (UProgressBar*)pHUDWidget->GetWidgetFromName(FName(*("pb_Allie" + FString::FromInt(i+1))));
				UProgressBar* opponent_health = (UProgressBar*)pHUDWidget->GetWidgetFromName(FName(*("pb_Opponent" + FString::FromInt(i+1))));
				if (allie_health != nullptr)
				{
					allie_health->PercentDelegate.BindUFunction(Manager->Player1Characters[i], "GetHealthPercentage");
					allie_health->SynchronizeProperties();
				}
				if (opponent_health != nullptr)
				{
					opponent_health->PercentDelegate.BindUFunction(Manager->Player2Characters[i], "GetHealthPercentage");
					opponent_health->SynchronizeProperties();
				}
			}
		
		}
	}
}

void AAnimalsOfWarHUD::SetNumSheeps(int NumSheeps)
{
	if (pNumSheepsText.IsValid())
	{
		pNumSheepsText->SetText(FText::FromString(FString::FromInt(NumSheeps)));
	}
}

void AAnimalsOfWarHUD::SetNumGrenades(int NumGrenades)
{
	if (pNumGrenadesText.IsValid())
	{
		pNumGrenadesText->SetText(FText::FromString(FString::FromInt(NumGrenades)));
	}
}

void AAnimalsOfWarHUD::UpdateCounter(int time)
{
	if (pCounterText.IsValid()) 
	{
		pCounterText->SetText(FText::FromString(FString::FromInt(time)));
	}
}

void AAnimalsOfWarHUD::LoadPossesCharacterData(AAnimalsOfWarCharacter* character)
{
	SetNumSheeps(character->NumSheeps);
	SetNumGrenades(character->NumGrenades);
}

void AAnimalsOfWarHUD::ShowAimImage(bool isVisible) 
{
	if (isVisible) {
		pAimImage->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		pAimImage->SetVisibility(ESlateVisibility::Hidden);
	}
	
}