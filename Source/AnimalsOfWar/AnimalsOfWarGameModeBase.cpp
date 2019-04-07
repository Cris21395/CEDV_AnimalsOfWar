// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarGameModeBase.h"
 
#include "UObject/ConstructorHelpers.h"


AAnimalsOfWarGameModeBase::AAnimalsOfWarGameModeBase() 
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_AnimalsOfWarCharacter"));
	if(PlayerPawnBPClass.Class != nullptr)
		DefaultPawnClass = PlayerPawnBPClass.Class;
	//HUDClass = 
}