// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalsOfWarCharacter.generated.h"

class AGrenade;

/**
 * Character class based on ThirdPersonCharacter template
 */
UCLASS()
class ANIMALSOFWAR_API AAnimalsOfWarCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnimalsOfWarCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	// Number of sheeps
	int NumSheeps;

	// Number of grenates
	int NumGrenades;

	// Character's life
	float Life;

protected:
	/** Called every frame */
	void Tick(float DeltaSeconds) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

private:
	/** Properties used to throw objects */
	bool bPressedThrowGrenade;
	bool bPressedThrowSheep;
	float ForceToThrow;

	/** Called for getting force to throw a grenade */
	UFUNCTION()
		void ForceToThrowGrenade();

	/** Called for getting force to throw a sheep */
	UFUNCTION()
		void ForceToThrowSheep();

	/** Called for throwing a grenade */
	UFUNCTION()
		void ThrowGrenade();

	/** Called for throwing a sheep */
	UFUNCTION()
		void ThrowSheep();

public:
	// Handles the event when actor overlaps with other object
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	// Called when character has to die
	UFUNCTION()
		void Die();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
