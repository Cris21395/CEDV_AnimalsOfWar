// Fill out your copyright notice in the Description page of Project Settings.

#include "Sheep.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
ASheep::ASheep()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	SheepMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SheepMesh"));
	SheepMesh->SetupAttachment(RootComponent);
	SheepMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Meshes/Sheep/sheep.sheep'")).Object);
}

// Called when the game starts or when spawned
void ASheep::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASheep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
