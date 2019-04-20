// Fill out your copyright notice in the Description page of Project Settings.

#include "Grenade.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"
#include "AnimalsOfWarCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Mesh;
		ConstructorHelpers::FObjectFinderOptional<UParticleSystem> Explosion_Particle_System;
		ConstructorHelpers::FObjectFinderOptional<USoundBase> Audio_Explosion;
		FConstructorStatics()
			: Mesh(TEXT("StaticMesh'/Game/Meshes/Grenade/Grenade.Grenade'"))
			, Explosion_Particle_System(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"))
			, Audio_Explosion(TEXT("/Game/StarterContent/Audio/Explosion01.Explosion01"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Mesh
	GrenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade"));
	GrenadeMesh->SetupAttachment(RootComponent);
	GrenadeMesh->SetStaticMesh(ConstructorStatics.Mesh.Get());
	GrenadeMesh->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);

	// Audio and explosion
	ExplosionParticleSystem = ConstructorStatics.Explosion_Particle_System.Get();
	AudioExplosion = ConstructorStatics.Audio_Explosion.Get();

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	//ProjectileComponent = NewObject<UProjectileMovementComponent>(this, UProjectileMovementComponent::StaticClass());
	ProjectileComponent->SetAutoActivate(false);
	ProjectileComponent->UpdatedComponent = GrenadeMesh.Get();
	ProjectileComponent->InitialSpeed = 10.f;
	ProjectileComponent->MaxSpeed = 30.f;
	ProjectileComponent->bRotationFollowsVelocity = true;
	ProjectileComponent->bShouldBounce = true;
	

	// Register OnHit event
	OnActorHit.AddDynamic(this, &AGrenade::OnHit);
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

void AGrenade::MakeThrowable()
{
	// Projectile Movement Component Setup
	//ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	//ProjectileComponent = NewObject<UProjectileMovementComponent>(this, UProjectileMovementComponent::StaticClass());
	//ProjectileComponent->UpdatedComponent = GrenadeMesh.Get();
	//ProjectileComponent->InitialSpeed = 10.f;
	//ProjectileComponent->MaxSpeed = 30.f;
	//ProjectileComponent->bRotationFollowsVelocity = true;
	//ProjectileComponent->bShouldBounce = true;
	ProjectileComponent->SetActive(true, true);
}

void AGrenade::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (OtherActor->IsA(AAnimalsOfWarCharacter::StaticClass()))
		{
			AAnimalsOfWarCharacter* Character = (AAnimalsOfWarCharacter*)OtherActor;

			// If Grenade has been thrown, we execute this logic
			if (!NormalImpulse.IsZero())
			{
				// Fire explosion if grenades collides with character by being thrown
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), Hit.Location);

				// Apply damage to character
				Character->Life -= Damage;

				// Destory character if life is less or equal to 0
				if (Character->Life <= 0)
					Character->Die();
			}
			// Otherwise, we increment the number of grenades
			else
			{
				Character->IncreaseGrenadeCounter();
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