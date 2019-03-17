// Fill out your copyright notice in the Description page of Project Settings.

#include "Subject.h"
#include "Observer.h"

void Subject::AddObserver(TScriptInterface<IObserver> Observer)
{
	Observers.Add((IObserver*)Observer.GetInterface());
}

void Subject::RemoveObserver(TScriptInterface<IObserver> Observer)
{
	Observers.Remove((IObserver*)Observer.GetInterface());
}

void Subject::OnNotify(UObject * Entity, EEvent Event)
{
	for (auto Observer : Observers) 
	{
		Observer->OnNotify(Entity, Event);
	}
}
