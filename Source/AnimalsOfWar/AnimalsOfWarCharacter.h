// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalsOfWarCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FCharacterDelegate, class AAnimalsOfWarCharacter*);

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

	// Called when a character has been hit
	FCharacterDelegate HitCharacterDelegate;

	// Called when a character dies
	FCharacterDelegate DeadCharacterDelegate;

	// Number of sheeps
	int NumSheeps;

	// Number of grenades
	int NumGrenades;

	// Name of the character
	FString CharacterName;

	// Character's health
	float Health;

protected:
	/** Called every frame */
	void Tick(float DeltaSeconds) override;

	/** Called when character was applied a damage */
	float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent,
		AController * EventInstigator, AActor * DamageCauser) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

private:
	/** Properties used to throw objects */
	bool bPressedThrowGrenade;
	bool bPressedThrowSheep;
	float ForceToThrow;

	/** Animation when character dies */
	UPROPERTY()
		TWeakObjectPtr<UAnimSequence> DieAnimation;

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

	/** Called by the HUD to check Health **/
	UFUNCTION()
		float GetHealthPercentage();

	/** Called when aiming **/
	UFUNCTION(BlueprintCallable, Category = "Aiming")
		void StartAiming(AActor* TargetActor);

	/** Called when stop aiming **/
	UFUNCTION(BlueprintCallable, Category = "Aiming")
		void StopAiming(AActor* TargetActor);

public:
	/** Handles the event when actor overlaps with other object **/
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	/** Called when character has to die **/
	UFUNCTION()
		void Die();

	/** Called when a sheep is picked up **/
	UFUNCTION()
		void SetSheepsCounter(int NumSheeps);

	/** Called when a grenade is picked up **/
	UFUNCTION()
		void SetGrenadesCounter(int NumGrenades);

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
