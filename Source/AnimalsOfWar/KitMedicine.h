// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "KitMedicine.generated.h"

UCLASS()
class ANIMALSOFWAR_API AKitMedicine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKitMedicine();

	// StaticMesh component for the KitMedicine
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = KitMedicine, meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr<UStaticMeshComponent> KitMesh;

	// Health applied to the character that uses this object
	int const Health = 25;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Handles the collision when this object collides with other one
	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	// Returns Kit Mesh subobject
	FORCEINLINE class UStaticMeshComponent* GetKitMesh() const { return KitMesh.Get(); }
};
