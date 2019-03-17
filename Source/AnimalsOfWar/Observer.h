// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EEvent.h"
#include "Observer.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UObserver : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface Observer class to implement observer pattern
 */
class ANIMALSOFWAR_API IObserver
{
	GENERATED_BODY()

public:
	// Virtual method to be implemented by observers
	virtual void OnNotify(UObject* Entity, EEvent Event) = 0;
};
