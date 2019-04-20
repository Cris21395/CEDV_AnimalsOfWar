// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grenade.h"
#include "ThrowableGrenade.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALSOFWAR_API AThrowableGrenade : public AGrenade
{
	GENERATED_BODY()

	AThrowableGrenade();

	// Component for the projectile movement
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Grenade, meta = (AllowPrivateAccess = "true"))
		//class UProjectileMovementComponent* ProjectileComponent;
};
