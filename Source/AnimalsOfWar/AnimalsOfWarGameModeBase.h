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
	float const MaxTurnTime = 30.0f;

	// After a turn this is the time that the player is given feedback
	// before the change of the possessed pawn
	float const FeedbackTime = 2.0f;

	// Remaining time in a turn
	float RemainingTurnTime;

private:
	// Pointer to HUD class
	TWeakObjectPtr<class AAnimalsOfWarHUD> HUD;

	// Pointer to AnimalsOfWarManager class
	TWeakObjectPtr<class AAnimalsOfWarManager> Manager;

	// Pointer to PlayerController class
	TWeakObjectPtr<class AAnimalsOfWarPlayerController> PlayerController;

	// Aux variable for seconds in HUD
	int HUDTime;

	// Called when the turn finishes and the character is not
	// able to be controlled and feedback is given to the player
	UFUNCTION()
		void EndTurn();

	// Called after feedback is been given and the turn is changed
	// to the other team
	UFUNCTION()
		void ChangeTurn();

protected:
	// Begin Play Method
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Called when there is a winner
	void ThereIsAWinner();
};
