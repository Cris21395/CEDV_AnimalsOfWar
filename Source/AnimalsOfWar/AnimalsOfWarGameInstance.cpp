// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarGameInstance.h"

void UAnimalsOfWarGameInstance::SetPlayer1Material(UMaterialInterface * Player1Material)
{
	Player1MaterialPointer = Player1Material->GetMaterial();
}

void UAnimalsOfWarGameInstance::SetPlayer2Material(UMaterialInterface * Player2Material)
{
	Player2MaterialPointer = Player2Material->GetMaterial();
}

void UAnimalsOfWarGameInstance::setTeam1(FText Text1)
{
	Team1 = Text1;
}

void UAnimalsOfWarGameInstance::setTeam2(FText Text2)
{
	Team2 = Text2;
}

