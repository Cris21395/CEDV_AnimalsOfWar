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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns Sheep Mesh subobject
	FORCEINLINE class UStaticMeshComponent* GetSheepMesh() const { return SheepMesh.Get(); }
};
