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

	// Update the counter text widget
	UFUNCTION()
		void UpdateCounter(int time);

	// When a character is possed must call this function
	UFUNCTION()
		void LoadPossesCharacterData(AAnimalsOfWarCharacter* character);

	// Set Visible Aim Image
	UFUNCTION()
		void ShowAimImage(bool isVisible);
};
