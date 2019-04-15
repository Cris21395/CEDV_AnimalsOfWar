// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarManager.h"
#include "AnimalsOfWarGameModeBase.h"
#include "AnimalsOfWarGameInstance.h"
#include "AnimalsOfWarCharacter.h"
#include "EngineMinimal.h"
#include "EngineUtils.h"

// Sets default values
AAnimalsOfWarManager::AAnimalsOfWarManager() {}

// Called when the game starts or when spawned
void AAnimalsOfWarManager::BeginPlay()
{
	Super::BeginPlay();

	UAnimalsOfWarGameInstance * GameInstance = (UAnimalsOfWarGameInstance*)GetWorld()->GetGameInstance();
	AAnimalsOfWarGameModeBase * GameModeBase = (AAnimalsOfWarGameModeBase*)GetWorld()->GetAuthGameMode();

	int NumbersPawnsToBeSpawns = GameModeBase->NumberOfPawns / 2;
	for (int i = 0; i < NumbersPawnsToBeSpawns; i++)
	{
		SpawnAnimalsRandomly(Player1TargetPoints[i], nullptr /* GameInstance->GetPlayer1Material() */);
		SpawnAnimalsRandomly(Player2TargetPoints[i], nullptr /* GameInstance->GetPlayer2Material() */);
	}
}

void AAnimalsOfWarManager::SpawnAnimalsRandomly(ATargetPoint * TargetPoint, UMaterial* Material)
{
	AAnimalsOfWarCharacter * Character = GetWorld()->SpawnActor<AAnimalsOfWarCharacter>
		(ToSpawn, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
	// Character->GetMesh()->SetMaterial(2, Material);
}
