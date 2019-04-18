// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Sheep.generated.h"

UCLASS()
class ANIMALSOFWAR_API ASheep : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASheep();

	// StaticMesh component for the sheep
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sheep, meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr<UStaticMeshComponent> SheepMesh;

	// Damage caused when a sheep hits character
	int const Damage = 50;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Pointer to explosion used to be fired when a sheep has hit a character
	UPROPERTY()
		TWeakObjectPtr<UParticleSystem> ExplosionParticleSystem;

	// Pointer to audio explosion used to be played along ExplosionParticleSystem
	UPROPERTY()
		TWeakObjectPtr<USoundBase> AudioExplosion;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Handles the collision when this object collides with other one
	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	// Returns Sheep Mesh subobject
	FORCEINLINE class UStaticMeshComponent* GetSheepMesh() const { return SheepMesh.Get(); }
};
