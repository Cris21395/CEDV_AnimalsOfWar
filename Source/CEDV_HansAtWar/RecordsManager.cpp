// Fill out your copyright notice in the Description page of Project Settings.

#include "RecordsManager.h"
#include "HansAtWarSaveGame.h"
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
		HansAtWarSaveGamePtr = Cast<UHansAtWarSaveGame>(UGameplayStatics::LoadGameFromSlot(SAVE_SLOT_NAME, USER_INDEX));
	}
	else
	{
		// Create an instance of a SaveGame object
		HansAtWarSaveGamePtr = Cast<UHansAtWarSaveGame>(UGameplayStatics::CreateSaveGameObject(UHansAtWarSaveGame::StaticClass()));
	}
}

TMap<FString, int> ARecordsManager::GetRecords() const
{
	return HansAtWarSaveGamePtr->Records;
}

void ARecordsManager::SaveNewRecord(FString TeamName, int HitHans)
{
	// Add a new record
	HansAtWarSaveGamePtr->Records.Add(TeamName, HitHans);

	// Order the TMap regarding the HitHans
	HansAtWarSaveGamePtr->Records.ValueSort([](const int& A, const int& B)
	{
		return A > B;
	});

	// Save the game
	UGameplayStatics::SaveGameToSlot(HansAtWarSaveGamePtr.Get(), HansAtWarSaveGamePtr->SaveSlotName, HansAtWarSaveGamePtr->UserIndex);

}