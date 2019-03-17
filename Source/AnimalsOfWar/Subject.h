// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "EEvent.h"

class IObserver;

/**
 * Subject class used to notify events
 */
class ANIMALSOFWAR_API Subject
{
public:
	// Register an observer
	void AddObserver(TScriptInterface<IObserver> Observer);

	// Remove a registered observer
	void RemoveObserver(TScriptInterface<IObserver> Observer);

protected:
	// Notify event as an Entity to observer
	void OnNotify(UObject* Entity, EEvent Event);

private:
	// Array of observers
	TArray <IObserver*> Observers;
};
