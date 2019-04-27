// Fill out your copyright notice in the Description page of Project Settings.

#include "RecordsManager.h"
#include "AnimalsOfWarSaveGame.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARecordsManager::ARecordsManager() {}

// Called when the game starts or when spawned
void ARecordsManager::BeginPlay()
{
	Super::BeginPlay();

	// if save game exist
	if (UGameplayStatics::DoesSaveGameExist(SAVE_SLOT_NAME, USER_INDEX))
	{
		// Create an instance of a LoadGame object
		AnimalsOfWarSaveGamePtr = Cast<UAnimalsOfWarSaveGame>(UGameplayStatics::LoadGameFromSlot(SAVE_SLOT_NAME, USER_INDEX));
	}
	else
	{
		// Create an instance of a SaveGame object
		AnimalsOfWarSaveGamePtr = Cast<UAnimalsOfWarSaveGame>(UGameplayStatics::CreateSaveGameObject(UAnimalsOfWarSaveGame::StaticClass()));
	}
}

TMap<FString, int> ARecordsManager::GetRecords() const
{
	return AnimalsOfWarSaveGamePtr->Records;
}

void ARecordsManager::SaveNewRecord(FString TeamName, int HitHans)
{
	// Add a new record
	AnimalsOfWarSaveGamePtr->Records.Add(TeamName, HitHans);

	// Order the TMap regarding the HitHans
	AnimalsOfWarSaveGamePtr->Records.ValueSort([](const int& A, const int& B)
	{
		return A > B;
	});

	// Save the game
	UGameplayStatics::SaveGameToSlot(AnimalsOfWarSaveGamePtr.Get(), AnimalsOfWarSaveGamePtr->SaveSlotName, AnimalsOfWarSaveGamePtr->UserIndex);
}

