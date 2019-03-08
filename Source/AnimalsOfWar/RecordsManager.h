// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RecordsManager.generated.h"

class UAOWSaveGame;

UCLASS()
class ANIMALSOFWAR_API ARecordsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARecordsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Gets the records of the game
	UFUNCTION(BlueprintCallable, Category = MapsAndSets)
		TMap<FString, int> GetRecords() const;

	/*
	* Saves a new record in the game
	* TeamName: the name of the team
	* HitHans: the substraction of hit hans from IA and player
	*/
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		void SaveNewRecord(FString TeamName, int HitHans);

private:
	// Pointer to the custom SaveGame class
	UPROPERTY()
		TWeakObjectPtr<UAOWSaveGame> AOWSaveGamePtr;
	
};
