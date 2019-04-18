// Fill out your copyright notice in the Description page of Project Settings.

#include "KitMedicine.h"
#include "EngineMinimal.h"
#include "AnimalsOfWarCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"


// Sets default values
AKitMedicine::AKitMedicine()
{
 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	KitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KitMesh"));
	KitMesh->SetupAttachment(RootComponent);
	KitMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>
		(TEXT("StaticMesh'/Game/Meshes/KitMedicine/First_Aid_Kit.First_Aid_Kit'")).Object);

	KitMesh->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);

	// Register OnHit event
	OnActorHit.AddDynamic(this, &AKitMedicine::OnHit);
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

void AKitMedicine::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (OtherActor->IsA(AAnimalsOfWarCharacter::StaticClass()))
		{
			AAnimalsOfWarCharacter* Character = (AAnimalsOfWarCharacter*)OtherActor;

			// Don't add extra life
			if (Character->Life < 100) 
			{
				Character->Life += Health;
				Destroy();
			}
		}
	}
}