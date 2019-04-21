// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalsOfWarCharacter.h"
#include "Grenade.h"
#include "ThrowableGrenade.h"
#include "Sheep.h"
#include "AnimalsOfWarHUD.h"
#include "Engine.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"


// Sets default values
AAnimalsOfWarCharacter::AAnimalsOfWarCharacter() : Health(100), NumSheeps(0), NumGrenades(0), ForceToThrow(0.0), bPressedThrowGrenade(false),
	bPressedThrowSheep(false)
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	// set our turn rates for input
	BaseTurnRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Allow overlap events
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	// Register custom event
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAnimalsOfWarCharacter::BeginOverlap);
}

// Called to bind functionality to input
void AAnimalsOfWarCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("ThrowGrenade", IE_Pressed, this, &AAnimalsOfWarCharacter::ForceToThrowGrenade);
	PlayerInputComponent->BindAction("ThrowSheep", IE_Pressed, this, &AAnimalsOfWarCharacter::ForceToThrowSheep);
	PlayerInputComponent->BindAction("ThrowGrenade", IE_Released, this, &AAnimalsOfWarCharacter::ThrowGrenade);
	PlayerInputComponent->BindAction("ThrowSheep", IE_Released, this, &AAnimalsOfWarCharacter::ThrowSheep);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAnimalsOfWarCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAnimalsOfWarCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

// Called every frame
void AAnimalsOfWarCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// It's not possible to throw grenades and sheeps at the same time
	if (bPressedThrowGrenade)
	{
		ForceToThrow += DeltaSeconds * 10000;
	}
	else if (bPressedThrowSheep) 
	{
		ForceToThrow += DeltaSeconds * 10000;
	}
}

float AAnimalsOfWarCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		Health -= ActualDamage;  
		if (Health <= 0.f)
		{
			Die();
		}
	}

	return ActualDamage;
}

void AAnimalsOfWarCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAnimalsOfWarCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AAnimalsOfWarCharacter::ForceToThrowGrenade()
{
	bPressedThrowGrenade = true;
	ForceToThrow = 0.0f;
}

void AAnimalsOfWarCharacter::ForceToThrowSheep()
{
	bPressedThrowSheep = true;
	ForceToThrow = 0.0f;
}

void AAnimalsOfWarCharacter::ThrowGrenade()
{
	if (NumGrenades > 0)
	{
		FVector CameraForward = FollowCamera->GetForwardVector();
		FVector SpawnLocation = GetActorLocation() + CameraForward * 250.0f;
		FRotator SpawnRotation = FollowCamera->GetComponentRotation();
		
		AGrenade* Grenade =(AGrenade*)GetWorld()->SpawnActor(AGrenade::StaticClass(), &SpawnLocation, &SpawnRotation);

		UStaticMeshComponent* Mesh = Grenade->GetGrenadeMesh();
		Mesh->SetSimulatePhysics(true);
		Mesh->SetPhysicsLinearVelocity(CameraForward * ForceToThrow);
		
		SetGrenadesCounter(-1);
		bPressedThrowGrenade = false;
	}
}

void AAnimalsOfWarCharacter::ThrowSheep()
{
	if (NumSheeps > 0)
	{
		FVector CameraForward = FollowCamera->GetForwardVector();
		FVector SpawnLocation = GetActorLocation() + CameraForward * 250.0f;
		FRotator SpawnRotation = FollowCamera->GetComponentRotation();

		ASheep* Sheep = (ASheep*)GetWorld()->SpawnActor(ASheep::StaticClass(), &SpawnLocation, &SpawnRotation);

		UStaticMeshComponent* Mesh = Sheep->GetSheepMesh();
		Mesh->SetSimulatePhysics(true);
		Mesh->SetPhysicsLinearVelocity(CameraForward * ForceToThrow);

		SetSheepsCounter(-1);
		bPressedThrowSheep = false;
	}
}

float AAnimalsOfWarCharacter::GetHealthPercentage()
{
	return Health/100.0f;
}

void AAnimalsOfWarCharacter::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor) 
	{
		if (OtherComp->IsA(UBoxComponent::StaticClass()))
		{
			Die();
		}
	}
}

void AAnimalsOfWarCharacter::Die()
{
	Health = 0.0f;
	// Start Die Animation

	// Destroy Actor after delay
	Destroy();
}

void AAnimalsOfWarCharacter::SetSheepsCounter(int NumSheeps)
{
	// Increase Counter
	this->NumSheeps += NumSheeps;

	// Notify HUD
	AAnimalsOfWarHUD* HUD = Cast<AAnimalsOfWarHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	HUD->SetNumSheeps(this->NumSheeps);
}

void AAnimalsOfWarCharacter::SetGrenadesCounter(int NumGrenades)
{
	// Set Counter
	this->NumGrenades += NumGrenades;

	// Notify HUD
	// TO DO: look for the active one (the one belonging to this character)
	AAnimalsOfWarHUD* HUD = Cast<AAnimalsOfWarHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	HUD->SetNumGrenades(this->NumGrenades);
}
