// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarPlayerController.h"
#include "AnimalsOfWarManager.h"
#include "AnimalsOfWarHUD.h"
#include "Engine.h"

AAnimalsOfWarPlayerController::AAnimalsOfWarPlayerController() : Player1PossesedIndex(-1), Player2PossesedIndex(-1), Turn(0)
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;
}

void AAnimalsOfWarPlayerController::NextTurn()
{
	TArray<APawn*> Characters;
	int IndexAux = 0;
	
	if (Turn)
	{
		Characters = Manager->Player1Characters;
		Player1PossesedIndex = ++Player1PossesedIndex % Characters.Num();
		IndexAux = Player1PossesedIndex;
	}
	else
	{
		Characters = Manager->Player2Characters;
		Player2PossesedIndex = ++Player2PossesedIndex % Characters.Num();
		IndexAux = Player2PossesedIndex;
	}

	// Posses next character
	Possess(Characters[IndexAux]);

	// Load in HUD possessed character data
	AAnimalsOfWarHUD* HUD = (AAnimalsOfWarHUD*)GetHUD();
	HUD->LoadPossesCharacterData((AAnimalsOfWarCharacter*)Characters[IndexAux]);

	// Switch between 0 and 1
	Turn = 1 - Turn;
}

void AAnimalsOfWarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get Manager reference
	for (TActorIterator<AAnimalsOfWarManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Conversion to smart pointer
		Manager = *ActorItr;
	}

	// Force to call BeginPlay to create the map before starting turn
	if (!Manager->HasActorBegunPlay()) Manager->DispatchBeginPlay();

	NextTurn(); // Initialize turn
}

void AAnimalsOfWarPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
