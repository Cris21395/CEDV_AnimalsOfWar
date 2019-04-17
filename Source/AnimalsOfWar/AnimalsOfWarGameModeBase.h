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
	int MaxPlayers = 2;

	// Begin Play Method
	void BeginPlay() override;

	// TODO: define a method to know which player has won	
};
