// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimalsOfWarPlayerController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Materials/Material.h"
#include "GameFramework/Actor.h"
#include "AnimalsOfWarManager.generated.h"

class AAnimalsOfWarCharacter;
class ASheep;

UCLASS()
class ANIMALSOFWAR_API AAnimalsOfWarManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimalsOfWarManager();

	// Array used to store the Player1's characters
	UPROPERTY()
		TArray<APawn*> Player1Characters;

	// Array used to store the Player1's characters
	UPROPERTY()
		TArray<APawn*> Player2Characters;
	
	//Player Controller 1
	TWeakObjectPtr <AAnimalsOfWarPlayerController>  PlayerController1;

	//Player Controller 2
	TWeakObjectPtr <AAnimalsOfWarPlayerController>  PlayerController2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Class to be associated in Editor to spawn character
	UPROPERTY(EditAnywhere)
		TSubclassOf<AAnimalsOfWarCharacter> CharacterToSpawn;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ASheep> SheepToSpawn;

	// Spawn points for player 1
	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> Player1TargetPoints;

	// Spawn points for player 2
	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> Player2TargetPoints;

	// Spawn points for Sheeps
	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> SheepTargetPoints;

	// Spawns digimons over the world
	AAnimalsOfWarCharacter * SpawnDigimonsRandomly(ATargetPoint* TargetPoint, UMaterial * Material);

	// Spawns sheeps over the world
	void SpawnSheepsRandomly(ATargetPoint* TargetPoint);
};
