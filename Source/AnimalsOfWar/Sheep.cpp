// Fill out your copyright notice in the Description page of Project Settings.

#include "Sheep.h"
#include "EngineMinimal.h"
#include "AnimalsOfWarCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
ASheep::ASheep()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Mesh;
		ConstructorHelpers::FObjectFinderOptional<UParticleSystem> Explosion_Particle_System;
		ConstructorHelpers::FObjectFinderOptional<USoundBase> Audio_Explosion;
		FConstructorStatics()
			: Mesh(TEXT("StaticMesh'/Game/Meshes/Sheep/sheep.sheep'"))
			, Explosion_Particle_System(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"))
			, Audio_Explosion(TEXT("/Game/StarterContent/Audio/Explosion01.Explosion01"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Mesh
	SheepMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SheepMesh"));
	SheepMesh->SetupAttachment(RootComponent);
	SheepMesh->SetStaticMesh(ConstructorStatics.Mesh.Get());
	SheepMesh->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	SheepMesh->SetNotifyRigidBodyCollision(true);

	// Audio and explosion
	ExplosionParticleSystem = ConstructorStatics.Explosion_Particle_System.Get();
	AudioExplosion = ConstructorStatics.Audio_Explosion.Get();

	// Register OnHit event
	OnActorHit.AddDynamic(this, &ASheep::OnHit);
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

void ASheep::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (OtherActor->IsA(AAnimalsOfWarCharacter::StaticClass()))
		{
			AAnimalsOfWarCharacter* Character = (AAnimalsOfWarCharacter*)OtherActor;

			// If Grenade has been thrown, we execute this logic
			if (!NormalImpulse.IsZero())
			{
				// Fire explosion
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), Hit.Location);

				// Apply damage to character
				Character->Life -= Damage;

				// Destory character if life is less or equal to 0
				if (Character->Life <= 0)
					Character->Die();
			}
			// Otherwise, we increment the number of grenates
			else
			{
				Character->SetSheepsCounter(1);
			}
		}
		else
		{
			// Fire explosion if grenades collides with other thing is not character
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), Hit.Location);
		}

		Destroy();
	}
}