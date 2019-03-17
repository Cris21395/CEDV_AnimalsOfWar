
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType) // BlueprintType is essential to include
enum class EEvent : uint8
{
	EVENT_NONE			UMETA(DisplayName = "Event: None"),
	EVENT_ERROR			UMETA(DisplayName = "Event: Error")
};