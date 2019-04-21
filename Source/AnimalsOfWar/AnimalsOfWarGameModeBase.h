// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AnimalsOfWarGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALSOFWAR_API AAnimalsOfWarGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AAnimalsOfWarGameModeBase();

	// Defines the number of players in the game
	int const MaxPlayers = 2;
	// Defines the max time of a turn in seconds
	float const MaxTurnTime = 15.0f;

	// Remaining time in a turn
	float RemainingTurnTime;

private:
	// Variable to hold a reference to the HUD
	TWeakObjectPtr<class AAnimalsOfWarHUD> HUD;

	// Varibale to hold a reference to the AnimalsOfWar manager
	TWeakObjectPtr<class AAnimalsOfWarManager> Manager;

	// Aux variable for seconds in HUD
	int HUDTime;

protected:
	// Begin Play Method
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// TODO: define a method to know which player has won	
};
