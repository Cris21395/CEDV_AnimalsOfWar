// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarManager.h"
#include "AnimalsOfWarGameInstance.h"
#include "AnimalsOfWarCharacter.h"
#include "Sheep.h"
#include "EngineMinimal.h"
#include "EngineUtils.h"

// Sets default values
AAnimalsOfWarManager::AAnimalsOfWarManager() {}

// Called when the game starts or when spawned
void AAnimalsOfWarManager::BeginPlay()
{
	Super::BeginPlay();

	UAnimalsOfWarGameInstance * GameInstance = (UAnimalsOfWarGameInstance*)GetWorld()->GetGameInstance();

	// It's the same which array to use. Both have the same number of elements
	int NumbersPawnsToBeSpawned = Player1TargetPoints.Num();
	for (int i = 0; i < NumbersPawnsToBeSpawned; i++)
	{
		// Add characters to these arrays
		Player1Characters.Add(SpawnDigimonsRandomly(Player1TargetPoints[i], GameInstance->GetPlayer1Material()));
		Player2Characters.Add(SpawnDigimonsRandomly(Player2TargetPoints[i], GameInstance->GetPlayer2Material()));
	}

	// Spawn sheeps
	int NumberActorsToBeSpawned = SheepTargetPoints.Num();
	for (int i = 0; i < NumberActorsToBeSpawned; i++) 
	{
		SpawnSheepsRandomly(SheepTargetPoints[i]);
	}
}

AAnimalsOfWarCharacter * AAnimalsOfWarManager::SpawnDigimonsRandomly(ATargetPoint * TargetPoint, UMaterial* Material)
{
	AAnimalsOfWarCharacter * Character = GetWorld()->SpawnActor<AAnimalsOfWarCharacter>
		(CharacterToSpawn, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
	Character->GetMesh()->SetMaterial(2, Material);

	return Character;
}

void AAnimalsOfWarManager::SpawnSheepsRandomly(ATargetPoint * TargetPoint)
{
	GetWorld()->SpawnActor<ASheep>(SheepToSpawn, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
}
