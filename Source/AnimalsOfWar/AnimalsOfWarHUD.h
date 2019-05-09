// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AnimalsOfWarHUD.generated.h"

class AAnimalsOfWarCharacter;

UCLASS()
class ANIMALSOFWAR_API AAnimalsOfWarHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AAnimalsOfWarHUD();

	// Reference to HUD widget
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pHUDWidget;

	// Variable to hold specifically the grenades TextBlock in the widget
	UPROPERTY()
		TWeakObjectPtr<class UTextBlock> pNumGrenadesText;

	// Variable to hold specifically the sheeps TextBlock in the widget
	UPROPERTY()
		TWeakObjectPtr<class UTextBlock> pNumSheepsText;

	// Variable to hold the character that is being possessed
	UPROPERTY()
		TWeakObjectPtr<class UTextBlock> pCurrentPlayerText;

	// Variable to hold specifically the counter TextBlock
	UPROPERTY()
		TWeakObjectPtr<class UTextBlock> pCounterText;

	//Variable to hold specifically the image of the aim
	UPROPERTY()
		TWeakObjectPtr<class UImage> pAimImage;

	// Reference to HUD Widget class
	class UClass* pHUDWidgetClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Set Sheeps text widget
	UFUNCTION()
		void SetNumSheeps(int NumGrenades);

	// Set Grenades text widget
	UFUNCTION()
		void SetNumGrenades(int NumSheeps);

	UFUNCTION()
		void SetCharacterName(FString Name);

	// Initialize HUD widgets
	UFUNCTION()
		void InitializeWidgetFromHUD(TArray<APawn*> Player1Characters, TArray<APawn*> Player2Characters);

	// Update the counter text widget
	UFUNCTION()
		void UpdateCounter(int Time);

	// When a character is possed must call this function
	UFUNCTION()
		void LoadPossesCharacterData(AAnimalsOfWarCharacter* Character);

	// Set Visible Aim Image
	UFUNCTION()
		void ShowAimImage(bool bIsVisible);
};
