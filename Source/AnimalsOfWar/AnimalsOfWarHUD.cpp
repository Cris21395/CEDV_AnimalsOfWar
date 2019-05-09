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
			pCurrentPlayerText = (UTextBlock*)pHUDWidget->GetWidgetFromName("Current_Player");
			pCounterText = (UTextBlock*)pHUDWidget->GetWidgetFromName("TimeCounter");
			pAimImage = (UImage*)pHUDWidget->GetWidgetFromName("AimImage");
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

void AAnimalsOfWarHUD::SetCharacterName(FString Name)
{
	if (pCurrentPlayerText.IsValid())
	{
		pCurrentPlayerText->SetText(FText::FromString(Name));
	}
}

void AAnimalsOfWarHUD::InitializeWidgetFromHUD(TArray<APawn*> Player1Characters, TArray<APawn*> Player2Characters)
{
	// It's the same to get array 1 as array 2
	int Size = Player1Characters.Num();

	for (int i = 0; i < Size; i++)
	{
		AAnimalsOfWarCharacter* Player1Character = Cast<AAnimalsOfWarCharacter>(Player1Characters[i]);
		AAnimalsOfWarCharacter* Player2Character = Cast<AAnimalsOfWarCharacter>(Player2Characters[i]);

		UProgressBar* Allie_health = (UProgressBar*)pHUDWidget->GetWidgetFromName(FName(*("pb_Allie" + FString::FromInt(i + 1))));
		UProgressBar* Opponent_health = (UProgressBar*)pHUDWidget->GetWidgetFromName(FName(*("pb_Opponent" + FString::FromInt(i + 1))));

		if (Allie_health != nullptr)
		{
			Allie_health->PercentDelegate.BindUFunction(Player1Character, "GetHealthPercentage");
			Allie_health->SynchronizeProperties();
		}

		if (Opponent_health != nullptr)
		{
			Opponent_health->PercentDelegate.BindUFunction(Player2Character, "GetHealthPercentage");
			Opponent_health->SynchronizeProperties();
		}

		UTextBlock* Allie_Text = (UTextBlock*)pHUDWidget->GetWidgetFromName(FName(*("pt_Allie" + FString::FromInt(i + 1))));
		UTextBlock* Opponent_Text = (UTextBlock*)pHUDWidget->GetWidgetFromName(FName(*("pt_Opponent" + FString::FromInt(i + 1))));

		if (Allie_Text != nullptr)
		{
			Allie_Text->SetText(FText::FromString(Player1Character->CharacterName));
		}

		if (Opponent_Text != nullptr)
		{
			Opponent_Text->SetText(FText::FromString(Player2Character->CharacterName));
		}
	}
}

void AAnimalsOfWarHUD::UpdateCounter(int Time)
{
	if (pCounterText.IsValid()) 
	{
		pCounterText->SetText(FText::FromString(FString::FromInt(Time)));
	}
}

void AAnimalsOfWarHUD::LoadPossesCharacterData(AAnimalsOfWarCharacter* Character)
{
	SetNumSheeps(Character->NumSheeps);
	SetNumGrenades(Character->NumGrenades);
	SetCharacterName(Character->CharacterName);
}

void AAnimalsOfWarHUD::ShowAimImage(bool bIsVisible) 
{
	if (bIsVisible) pAimImage->SetVisibility(ESlateVisibility::Visible);
	else pAimImage->SetVisibility(ESlateVisibility::Hidden);	
}