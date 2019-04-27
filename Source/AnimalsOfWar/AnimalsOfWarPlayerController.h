// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AnimalsOfWarPlayerController.generated.h"

/**
 * Custom class to handle the player(s) of the game
 */
UCLASS()
class ANIMALSOFWAR_API AAnimalsOfWarPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAnimalsOfWarPlayerController();

	// Handles the turns
	void NextTurn();

private:
	// 0 -> Player1 | 1 -> Player2
	short int Turn;

	// Index of the possesed character for Player1
	int Player1PossesedIndex;

	// Index of the possesed character for Player2
	int Player2PossesedIndex;

	// Pointer to Manager class
	UPROPERTY()
		TWeakObjectPtr<class AAnimalsOfWarManager> Manager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
