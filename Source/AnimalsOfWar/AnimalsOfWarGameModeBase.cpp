// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarGameModeBase.h"
#include "AnimalsOfWarPlayerController.h"
#include "AnimalsOfWarCharacter.h"
#include "AnimalsOfWarManager.h"
#include "AnimalsOfWarHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "UMG.h"
#include "WidgetBlueprintLibrary.h"

AAnimalsOfWarGameModeBase::AAnimalsOfWarGameModeBase() 
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = nullptr;
	PlayerControllerClass = AAnimalsOfWarPlayerController::StaticClass();
	HUDClass = AAnimalsOfWarHUD::StaticClass();
}

void AAnimalsOfWarGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Init the remaining time
	RemainingTurnTime = MaxTurnTime;
	HUDTime = floor(RemainingTurnTime);

	// Get HUD reference
	HUD = Cast<AAnimalsOfWarHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// Get PlayerController reference
	PlayerController = Cast<AAnimalsOfWarPlayerController>(GetWorld()->GetFirstPlayerController());
}

void AAnimalsOfWarGameModeBase::Tick(float DeltaTime)
{
	RemainingTurnTime -= DeltaTime;

	// A second 
	if (HUDTime > floor(RemainingTurnTime) && HUDTime>0) 
	{
		HUDTime = floor(RemainingTurnTime);
		HUD->UpdateCounter(HUDTime);
		if (HUDTime <= 0) {
			EndTurn();
		}
	}
	// Check turn timeout
	if (RemainingTurnTime <= -FeedbackTime) // Negative as reminingTurnTime keep decreasing
	{
		ChangeTurn();
	}
}

void AAnimalsOfWarGameModeBase::ThereIsAWinner()
{
	// Spend 5 seconds to load records map. Without it, map is run so quickly
	FTimerDelegate TimerDelegate;
	FTimerHandle Handle;
	TimerDelegate.BindLambda([&]() 
	{ 
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Maps/Records"), TRAVEL_Absolute);
	});
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerDelegate, 3.0f, false);
}

void AAnimalsOfWarGameModeBase::EndTurn()
{
	//Obtain pawn of this character
	AAnimalsOfWarCharacter * Character = Cast<AAnimalsOfWarCharacter>(PlayerController.Get()->GetPawn());

	//Disable Input for these character
	if (Character) Character->DisableInput(PlayerController.Get());

	// Show feedback text and play animation
	HUD->ShowEndTurnFeedback();
}

void AAnimalsOfWarGameModeBase::ChangeTurn()
{
	AAnimalsOfWarCharacter * Character = Cast<AAnimalsOfWarCharacter>(PlayerController.Get()->GetPawn());

	// Reset counter
	RemainingTurnTime = MaxTurnTime;
	HUDTime = floor(RemainingTurnTime);

	//Hide aiming cross
	HUD->ShowAimImage(false);

	//Enable Input when you change the character
	if (Character) Character->EnableInput(PlayerController.Get());
	PlayerController->NextTurn();
}