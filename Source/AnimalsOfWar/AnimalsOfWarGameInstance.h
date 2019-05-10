// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Materials/Material.h"
#include "AnimalsOfWarGameInstance.generated.h"

/**
 * Custom Game instance class that store data for being carried between levels
 */
UCLASS()
class ANIMALSOFWAR_API UAnimalsOfWarGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	// Name of the Team1
	UPROPERTY()
		FText Team1;

	// Name of Team2
	UPROPERTY()
		FText Team2;

	// Pointer to material used for Player1's animals
	UPROPERTY()
		TWeakObjectPtr<UMaterial> Player1MaterialPointer;

	// Pointer to aterial used for Player2's animals
	UPROPERTY()
		TWeakObjectPtr<UMaterial> Player2MaterialPointer;

	// Winner of the game
	UPROPERTY()
		TMap<FString, int> Winner;


public:
	// Set Player 1 material
	UFUNCTION(BlueprintCallable, Category = PlayerMaterial)
		void SetPlayer1Material(UMaterialInterface * Player1Material);

	// Set Player 2 material
	UFUNCTION(BlueprintCallable, Category = PlayerMaterial)
		void SetPlayer2Material(UMaterialInterface* Player2Material);

	// Sets Text of Team1
	UFUNCTION(BlueprintCallable, Category = TextTeam)
		void SetTeam1(FText TeamText1) { Team1 = TeamText1; }

	// Sets Text of Team2
	UFUNCTION(BlueprintCallable, Category = TextTeam)
		void SetTeam2(FText TeamText2) { Team2 = TeamText2; };

	// Sets the winner of the game
	UFUNCTION(BlueprintCallable, Category = GameWinner)
		void SetWinner(FString Team, int HitHans) { Winner.Add(Team, HitHans); }

	// Gets Text of Team1
	UFUNCTION(BlueprintCallable, Category = TextTeam)
		FText GetTeam1() { return Team1; }

	// Gets Text of Team2
	UFUNCTION(BlueprintCallable, Category = TextTeam)
		FText GetTeam2() { return Team2; }

	//Gets Material for player1
	UFUNCTION(BlueprintCallable, Category = PlayerMaterial)
		UMaterial* GetPlayer1Material() { return Player1MaterialPointer.Get(); }

	// Gets Material for player2
	UFUNCTION(BlueprintCallable, Category = PlayerMaterial)
		UMaterial* GetPlayer2Material() { return Player2MaterialPointer.Get(); }

	// Gets the winner of the game
	UFUNCTION(BlueprintCallable, Category = GameWinner)
		TMap <FString, int> GetWinner() { return Winner; }
};
