// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarManager.h"
#include "AnimalsOfWarGameInstance.h"
#include "AnimalsOfWarCharacter.h"
#include "AnimalsOfWarHUD.h"
#include "KitMedicine.h"
#include "Sheep.h"
#include "Grenade.h"
#include "EngineMinimal.h"
#include "EngineUtils.h"

// Sets default values
AAnimalsOfWarManager::AAnimalsOfWarManager() {}

// Called when the game starts or when spawned
void AAnimalsOfWarManager::BeginPlay()
{
	Super::BeginPlay();

	UAnimalsOfWarGameInstance * GameInstance = (UAnimalsOfWarGameInstance*)GetWorld()->GetGameInstance();
	//Player Controllers
	PlayerController1 = (AAnimalsOfWarPlayerController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController2 = (AAnimalsOfWarPlayerController*)UGameplayStatics::GetPlayerController(GetWorld(), 1);

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
	NextCharacterPlayer1();
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

void AAnimalsOfWarManager::SpawnKitsRandomly(ATargetPoint * TargetPoint)
{
	GetWorld()->SpawnActor<AKitMedicine>(KitToSpawn, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
}

void AAnimalsOfWarManager::SpawnGrenadesRandomly(ATargetPoint * TargetPoint)
{
	GetWorld()->SpawnActor<AGrenade>(GrenadeToSpawn, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
}

void AAnimalsOfWarManager::NextCharacterPlayer1()
{
	// Calculate next index
	Player1PossesedIndex = ++Player1PossesedIndex % Player1Characters.Num();
	// Posses next character
	PlayerController1->Possess(Player1Characters[Player1PossesedIndex]);
	// Load in HUD possessed character data
	AAnimalsOfWarHUD* HUD = Cast<AAnimalsOfWarHUD>(PlayerController1->GetHUD());
	HUD->LoadPossesCharacterData((AAnimalsOfWarCharacter*)Player1Characters[Player1PossesedIndex]);
}