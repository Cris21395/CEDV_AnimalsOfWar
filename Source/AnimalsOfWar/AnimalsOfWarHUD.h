// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AnimalsOfWarHUD.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALSOFWAR_API AAnimalsOfWarHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AAnimalsOfWarHUD();

	void BeginPlay() override;

private:
	// Reference to HUD widget
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pHUDWidget;

	// Reference to HUD Widget class
	class UClass* pHUDWidgetClass;
	
	
};
