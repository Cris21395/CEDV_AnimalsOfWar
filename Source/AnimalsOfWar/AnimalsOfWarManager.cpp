// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarManager.h"
#include "AnimalsOfWarCharacter.h"
#include "AnimalsOfWarGameModeBase.h"
#include "AnimalsOfWarGameInstance.h"
#include "AchievementManager.h"
#include "AnimalsOfWarHUD.h"
#include "EngineMinimal.h"
#include "EngineUtils.h"
#include "Grenade.h"
#include "KitMedicine.h"
#include "Sheep.h"

// Sets default values
AAnimalsOfWarManager::AAnimalsOfWarManager() 
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAnimalsOfWarManager::BeginPlay()
{
	Super::BeginPlay();

	// Get GameInstance reference
	UAnimalsOfWarGameInstance * GameInstance = Cast<UAnimalsOfWarGameInstance>(GetWorld()->GetGameInstance());

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

	//Spawn KitMedicine
	int NumberKitsToBeSpawned = KitTargetPoints.Num();
	for (int i = 0; i < NumberKitsToBeSpawned; i++)
	{
		SpawnKitsRandomly(KitTargetPoints[i]);
	}

	//Spawn Grenades
	int NumberGrenadesToBeSpawned = GrenadeTargetPoints.Num();
	for (int i = 0; i < NumberGrenadesToBeSpawned; i++)
	{
		SpawnGrenadesRandomly(GrenadeTargetPoints[i]);
	}
}

// Called every frame
void AAnimalsOfWarManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AAnimalsOfWarCharacter * AAnimalsOfWarManager::SpawnDigimonsRandomly(ATargetPoint * TargetPoint, UMaterial* Material)
{
	AAnimalsOfWarCharacter * Character = GetWorld()->SpawnActor<AAnimalsOfWarCharacter>
		(CharacterToSpawn, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
	Character->GetMesh()->SetMaterial(2, Material);

	// Register DereferenceCharacter method to be called when character has died
	Character->DeadCharacterDelegate.BindUObject(this, &AAnimalsOfWarManager::DereferenceCharacter);

	return Character;
}

void AAnimalsOfWarManager::DereferenceCharacter(AAnimalsOfWarCharacter * Character)
{
	AchievementManager->OnNotifyDelegate.ExecuteIfBound(this, EnumEvent::EVENT_HIT_CHARACTER);

	int RemovedItem = Player1Characters.Remove(Character);

	if (Player1Characters.Num() == 0) 
	{
		UAnimalsOfWarGameInstance * GameInstance = Cast<UAnimalsOfWarGameInstance>
			(GetWorld()->GetGameInstance());
		FString Team = GameInstance->GetTeam2().ToString();
		int HitHans = Player2Characters.Num() - Player1Characters.Num();
		GameInstance->SetWinner(Team, HitHans);

		AAnimalsOfWarGameModeBase* GameModeBase = Cast<AAnimalsOfWarGameModeBase>
			(GetWorld()->GetAuthGameMode());
		GameModeBase->ThereIsAWinner();
	}

	if (RemovedItem != 0) return;

	Player2Characters.Remove(Character);

	if (Player2Characters.Num() == 0)
	{
		UAnimalsOfWarGameInstance * GameInstance = Cast<UAnimalsOfWarGameInstance>
			(GetWorld()->GetGameInstance());
		FString Team = GameInstance->GetTeam1().ToString();
		int HitHans = Player1Characters.Num() - Player2Characters.Num();
		GameInstance->SetWinner(Team, HitHans);

		AAnimalsOfWarGameModeBase* GameModeBase = Cast<AAnimalsOfWarGameModeBase>
			(GetWorld()->GetAuthGameMode());
		GameModeBase->ThereIsAWinner();
	}
}

void AAnimalsOfWarManager::SpawnSheepsRandomly(ATargetPoint * TargetPoint)
{
	GetWorld()->SpawnActor<ASheep>(SheepToSpawn, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
}

void AAnimalsOfWarManager::SpawnKitsRandomly(ATargetPoint * TargetPoint)
{
	GetWorld()->SpawnActor<AKitMedicine>(KitToSpawn, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
}

void AAnimalsOfWarManager::SpawnGrenadesRandomly(ATargetPoint * TargetPoint)
{
	GetWorld()->SpawnActor<AGrenade>(GrenadeToSpawn, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
}