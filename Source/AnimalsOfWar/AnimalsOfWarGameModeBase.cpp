// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarGameModeBase.h"
#include "AnimalsOfWarPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "AnimalsOfWarHUD.h"
#include "Engine.h"


AAnimalsOfWarGameModeBase::AAnimalsOfWarGameModeBase() 
{

	PlayerControllerClass = AAnimalsOfWarPlayerController::StaticClass();
	HUDClass = AAnimalsOfWarHUD::StaticClass();
}

void AAnimalsOfWarGameModeBase::BeginPlay()
{
	UGameplayStatics::CreatePlayer(GetWorld(), 0, true);
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
}