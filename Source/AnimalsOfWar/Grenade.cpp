// Fill out your copyright notice in the Description page of Project Settings.

#include "Grenade.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"


// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GrenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SheepMesh"));
	GrenadeMesh->SetupAttachment(RootComponent);
	GrenadeMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Meshes/Grenade/Grenade'")).Object); 

}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

