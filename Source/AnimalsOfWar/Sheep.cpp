// Fill out your copyright notice in the Description page of Project Settings.

#include "Sheep.h"


// Sets default values
ASheep::ASheep()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SheepMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SheepMesh"));
	SheepMesh->SetupAttachment(RootComponent);
	SheepMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Textures/Sheep/sheep'")).Object);
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

