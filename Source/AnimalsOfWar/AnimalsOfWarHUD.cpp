// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarHUD.h"

#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"

AAnimalsOfWarHUD::AAnimalsOfWarHUD(){
	struct FConstructorStatics
	{
		ConstructorHelpers::FClassFinder<UUserWidget> HUDWidgetObject;
		FConstructorStatics()
			: HUDWidgetObject(TEXT("/Game/Blueprints/UI/BP_HUDCharacter"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;
	
	// Save pointer to widgets
	pHUDWidgetClass = ConstructorStatics.HUDWidgetObject.Class;
}

void AAnimalsOfWarHUD::BeginPlay() 
{
	// Add widget to viewport
	if (pHUDWidgetClass) {
		pHUDWidget = CreateWidget<UUserWidget>(this->GetOwningPlayerController(), this->pHUDWidgetClass);
		pHUDWidget->AddToViewport();
	}
}


