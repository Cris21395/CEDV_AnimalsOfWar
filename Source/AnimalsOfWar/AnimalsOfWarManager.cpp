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

	AAnimalsOfWarGameModeBase * GameModeBase = (AAnimalsOfWarGameModeBase*)GetWorld()->GetAuthGameMode();
	int NumbersPawnsToBeSpawns = GameModeBase->NumberOfPawns / 2;
	for (int i = 0; i < NumbersPawnsToBeSpawns; i++)
	{
		SpawnAnimalsRandomly(Player1TargetPoints[i]);
		SpawnAnimalsRandomly(Player2TargetPoints[i]);
	}
}

void AAnimalsOfWarManager::SpawnAnimalsRandomly(ATargetPoint * TargetPoint)
{
	AAnimalsOfWarCharacter * Character = GetWorld()->SpawnActor<AAnimalsOfWarCharacter>
		(ToSpawn, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());

	/*static ConstructorHelpers::FObjectFinderOptional<UMaterial> Material(TEXT("Material'/Game/Meshes/Character_Veemon/mat1.mat1'"));
	UAnimalsOfWarGameInstance * GameInstance = (UAnimalsOfWarGameInstance*)GetWorld()->GetGameInstance();
	Character->GetMesh()->SetMaterial(2, Material.Get());*/
}
