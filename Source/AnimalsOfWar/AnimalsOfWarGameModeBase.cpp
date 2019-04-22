// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarGameModeBase.h"
#include "AnimalsOfWarPlayerController.h"
#include "AnimalsOfWarCharacter.h"
#include "AnimalsOfWarManager.h"
#include "AnimalsOfWarHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "UMG.h"
#include "WidgetBlueprintLibrary.h"


AAnimalsOfWarGameModeBase::AAnimalsOfWarGameModeBase() 
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = nullptr;
	PlayerControllerClass = AAnimalsOfWarPlayerController::StaticClass();
	HUDClass = AAnimalsOfWarHUD::StaticClass();
}

void AAnimalsOfWarGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::CreatePlayer(GetWorld(), 0, true);
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);

	// Init the remaining time
	RemainingTurnTime = MaxTurnTime;
	HUDTime = floor(RemainingTurnTime);

	// Get HUD reference
	HUD = Cast<AAnimalsOfWarHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	// Get Manager reference

	for (TActorIterator<AAnimalsOfWarManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Conversion to smart pointer
		Manager = *ActorItr;
	}
}

void AAnimalsOfWarGameModeBase::Tick(float DeltaTime)
{
	//Obtain player controller
	AAnimalsOfWarPlayerController* PlayerController1 = (AAnimalsOfWarPlayerController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//Obtain pawn of this character
	AAnimalsOfWarCharacter * Character = (AAnimalsOfWarCharacter *)PlayerController1->GetPawn();
	RemainingTurnTime -= DeltaTime;

	// A second 
	if (HUDTime > floor(RemainingTurnTime)) 
	{
		HUDTime = floor(RemainingTurnTime);
		HUD->UpdateCounter(HUDTime);
		if (HUDTime == 2) {
			
			//Disable Input for these character
			Character->DisableInput(PlayerController1);
		}
	}
	// Check turn timeout
	if (RemainingTurnTime <= 0.0f) 
	{
		// Reset counter
		RemainingTurnTime = MaxTurnTime;
		HUDTime = floor(RemainingTurnTime);

		//Enable Input when you change the character
		//MUST BE BEFORE THE METHOD BECAUSE AFTER IT WILL CHANGE THE PAWN
		Character->EnableInput(PlayerController1);
		// Change turn to diferrent character of the same PlayerController
		Manager->NextCharacterPlayer1();

	}

}