// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarHUD.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"
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
		}
	}
}

void AAnimalsOfWarHUD::IncreaseNumSheeps(int NumSheeps)
{
	if (pNumSheepsText.IsValid())
	{
		pNumSheepsText->SetText(FText::FromString(FString::FromInt(NumSheeps)));
	}
}

void AAnimalsOfWarHUD::IncreaseNumGrenades(int NumGrenades)
{
	if (pNumGrenadesText.IsValid())
	{
		pNumGrenadesText->SetText(FText::FromString(FString::FromInt(NumGrenades)));
	}
}