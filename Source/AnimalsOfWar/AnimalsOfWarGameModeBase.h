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

protected:
	// Begin Play Method
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// TODO: define a method to know which player has won	
};
