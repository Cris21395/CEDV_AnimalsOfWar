// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarManager.h"
#include "AnimalsOfWarCharacter.h"
#include "AnimalsOfWarGameModeBase.h"
#include "AnimalsOfWarGameInstance.h"
#include "AnimalsOfWarPlayerController.h"
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
		// Prepare parameters
		UMaterial* Player1Material = GameInstance->GetPlayer1Material();
		UMaterial* Player2Material = GameInstance->GetPlayer2Material();
		FString CharacterName1 = GameInstance->GetTeam1().ToString() + FString(TEXT(" ")) + FString::FromInt(i + 1);
		FString CharacterName2 = GameInstance->GetTeam2().ToString() + FString(TEXT(" ")) + FString::FromInt(i + 1);

		// Add characters to these arrays
		Player1Characters.Add(SpawnDigimonsRandomly(Player1TargetPoints[i], Player1Material, CharacterName1));
		Player2Characters.Add(SpawnDigimonsRandomly(Player2TargetPoints[i], Player2Material, CharacterName2));
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

	// Initialize widgets after spawining all objects
	AAnimalsOfWarPlayerController* PlayerController = Cast<AAnimalsOfWarPlayerController>
		(GetWorld()->GetFirstPlayerController());
	AAnimalsOfWarHUD* HUD = Cast<AAnimalsOfWarHUD>(PlayerController->GetHUD());

	// Force to call BeginPlay to save pointers
	if (!HUD->HasActorBegunPlay()) HUD->DispatchBeginPlay();
	HUD->InitializeWidgetFromHUD(Player1Characters, Player2Characters);
}

// Called every frame
void AAnimalsOfWarManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AAnimalsOfWarCharacter * AAnimalsOfWarManager::SpawnDigimonsRandomly(ATargetPoint * TargetPoint, 
	UMaterial* Material, FString CharacterName)
{
	AAnimalsOfWarCharacter * Character = GetWorld()->SpawnActor<AAnimalsOfWarCharacter>
		(CharacterToSpawn, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
	Character->CharacterName = CharacterName;
	Character->GetMesh()->SetMaterial(2, Material);

	// Register methods to be called when character execute a delegate
	Character->HitCharacterDelegate.BindUObject(this, &AAnimalsOfWarManager::HandleHitOfCharacter);
	Character->DeadCharacterDelegate.BindUObject(this, &AAnimalsOfWarManager::RemoveCharacterFromArrayWhenDie);

	return Character;
}

void AAnimalsOfWarManager::HandleHitOfCharacter(AAnimalsOfWarCharacter * Character)
{
	AchievementManager->OnNotifyDelegate.ExecuteIfBound(Character, EnumEvent::EVENT_HIT_CHARACTER);
}

void AAnimalsOfWarManager::RemoveCharacterFromArrayWhenDie(AAnimalsOfWarCharacter * Character)
{
	int RemovedItem = Player1Characters.Remove(Character);

	if (RemovedItem != 0)
	{
		if (Player1Characters.Num() == 0)
		{
			// Win player 2
			HandleFinishOfGame(1);
		}
	}
	else
	{
		Player2Characters.Remove(Character);

		if (Player2Characters.Num() == 0)
		{
			// Win Player 1
			HandleFinishOfGame(0);
		}
	}
}

void AAnimalsOfWarManager::HandleFinishOfGame(short int Team)
{
	UAnimalsOfWarGameInstance * GameInstance = Cast<UAnimalsOfWarGameInstance>(GetWorld()->GetGameInstance());

	// Set a Winner - Player 1
	if (Team == 0)
	{
		FString NameTeam = GameInstance->GetTeam1().ToString();
		int HitHans = Player1Characters.Num() - Player2Characters.Num();
		GameInstance->SetWinner(NameTeam, HitHans);
	}
	// Set a Winner - Player 2
	else
	{
		FString NameTeam = GameInstance->GetTeam2().ToString();
		int HitHans = Player2Characters.Num() - Player1Characters.Num();
		GameInstance->SetWinner(NameTeam, HitHans);
	}

	AAnimalsOfWarGameModeBase* GameModeBase = Cast<AAnimalsOfWarGameModeBase>(GetWorld()->GetAuthGameMode());
	GameModeBase->ThereIsAWinner();
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