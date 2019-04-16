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
	// Pointer to material used for Player1's animals
	UPROPERTY()
		TWeakObjectPtr<UMaterial> Player1MaterialPointer;

	// Pointer to aterial used for Player2's animals
	UPROPERTY()
		TWeakObjectPtr<UMaterial> Player2MaterialPointer;

	// Name of the Team1
	UPROPERTY()
		FText Team1;

	// Name of Team2
	UPROPERTY()
		FText Team2;

public:
	// Set Player 1 material
	UFUNCTION(BlueprintCallable, Category = PlayerMaterial)
		void SetPlayer1Material(UMaterialInterface * Player1Material);

	// Set Player 2 material
	UFUNCTION(BlueprintCallable, Category = PlayerMaterial)
		void SetPlayer2Material(UMaterialInterface* Player2Material);

	// Get Text of Team1
	class FText GetTeam1() { return Team1; }

	// Get Text of Team2
	class FText GetTeam2() { return Team2; }

	// Get Player 1 material
	class UMaterial* GetPlayer1Material() { return Player1MaterialPointer.Get(); }

	// Get Player 2 material
	class UMaterial* GetPlayer2Material() { return Player2MaterialPointer.Get(); }

	// Set Text of Team1
	UFUNCTION(BlueprintCallable, Category = TextTeam)
		void setTeam1(FText Text1);
	// Set Text of Team2
	UFUNCTION(BlueprintCallable, Category = TextTeam)
		void setTeam2(FText Text2);

	//Get Text of Team1
	UFUNCTION(BlueprintCallable, Category = TextTeam)
		FText GetTeam1Text() { return Team1; }

	// Get Text of Team2
	UFUNCTION(BlueprintCallable, Category = TextTeam)
		FText GetTeam2Text() { return Team2; }
};
