// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Grenade.generated.h"

UCLASS()
class ANIMALSOFWAR_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenade();

	// StaticMesh component for the grenade
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Grenade, meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr<UStaticMeshComponent> GrenadeMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE class UStaticMeshComponent* GetGrenadeMesh() const { return GrenadeMesh.Get(); }
	
};
