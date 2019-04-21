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
class AKitMedicine;
class AGrenade;

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

	// Called when the next character must be possesed for PC1
	UFUNCTION()
		void NextCharacterPlayer1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Index of the possesed character for PC1
	int Player1PossesedIndex = -1;

	// Class to be associated in Editor to spawn character
	UPROPERTY(EditAnywhere)
		TSubclassOf<AAnimalsOfWarCharacter> CharacterToSpawn;

	// Class to be associated in Editor to spawn sheep
	UPROPERTY(EditAnywhere)
		TSubclassOf<ASheep> SheepToSpawn;

	// Class to be associated in Editor to spawn kit medicine
	UPROPERTY(EditAnywhere)
		TSubclassOf<AKitMedicine> KitToSpawn;

	// Class to be associated in Editor to spawn grenade
	UPROPERTY(EditAnywhere)
		TSubclassOf<AGrenade> GrenadeToSpawn;

	// Spawn points for player 1
	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> Player1TargetPoints;

	// Spawn points for player 2
	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> Player2TargetPoints;

	// Spawn points for Sheeps
	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> SheepTargetPoints;

	//Spawn point for Kits
	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> KitTargetPoints;

	//Spawn point for grenates
	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> GrenadeTargetPoints;

	// Spawns sheeps over the world
	void SpawnSheepsRandomly(ATargetPoint* TargetPoint);

	//Spawns kits over the world
	void SpawnKitsRandomly(ATargetPoint* TargetPoint);

	//Spawns grenades over the world
	void SpawnGrenadesRandomly(ATargetPoint* TargetPoint);

	// Spawns digimons over the world
	AAnimalsOfWarCharacter * SpawnDigimonsRandomly(ATargetPoint* TargetPoint, UMaterial * Material);

};
