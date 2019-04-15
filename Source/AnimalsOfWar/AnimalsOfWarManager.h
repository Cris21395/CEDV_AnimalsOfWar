// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "AnimalsOfWarManager.generated.h"

class AAnimalsOfWarCharacter;

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Class to be associated in Editor to spawn character
	UPROPERTY(EditAnywhere)
		TSubclassOf<AAnimalsOfWarCharacter> ToSpawn;

	// Spawn points for player 1
	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> Player1TargetPoints;

	// Spawn points for player 2
	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> Player2TargetPoints;

	// Spawns animals over the world
	void SpawnAnimalsRandomly(ATargetPoint* TargetPoint);
};
