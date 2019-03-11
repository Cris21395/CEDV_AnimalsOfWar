// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AnimalsOfWarSaveGame.generated.h"

#define SAVE_SLOT_NAME "HansAtWarSaveSlot"
#define USER_INDEX 0

/**
 * Custom class to save data of AnimalsOfWar
 */
UCLASS()
class ANIMALSOFWAR_API UAnimalsOfWarSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UAnimalsOfWarSaveGame();

	// Map that contains a name associated with its point
	UPROPERTY(VisibleAnywhere, Category = Basic)
		TMap<FString, int> Records;

	// Save slot name to read saved data
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	// User index to read saved data
	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;
};
