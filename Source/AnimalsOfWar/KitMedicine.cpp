// Fill out your copyright notice in the Description page of Project Settings.

#include "KitMedicine.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"


// Sets default values
AKitMedicine::AKitMedicine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	KitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KitMesh"));
	KitMesh->SetupAttachment(RootComponent);
	KitMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Meshes/KitMedicine/First_Aid_Kit'")).Object);
}

// Called when the game starts or when spawned
void AKitMedicine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKitMedicine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

