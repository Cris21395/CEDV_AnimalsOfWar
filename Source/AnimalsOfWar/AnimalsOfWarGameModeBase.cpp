// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarGameModeBase.h"
#include "AnimalsOfWarPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "AnimalsOfWarHUD.h"


AAnimalsOfWarGameModeBase::AAnimalsOfWarGameModeBase() 
{
	PlayerControllerClass = AAnimalsOfWarPlayerController::StaticClass();
	HUDClass = AAnimalsOfWarHUD::StaticClass();
}