// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Gauntlet.h"
#include "GauntletCharacter.h"

//////////////////////////////////////////////////////////////////////////
// ATestCharacter

AGauntletCharacter::AGauntletCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character doesn't move in the direction of input...	
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 1200.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = false; // Don't rotate the arm based on the controller
	CameraBoom->bAbsoluteRotation = true; // Use an absolute rotation for the camera
	CameraBoom->RelativeRotation = FRotator(-60.0f, 0.0f, 0.0f); // Set the viewing angle of the camera.

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	//BlinkCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BlinkCollider"));
	//BlinkCollider->InitCapsuleSize(42.f, 96.0f);


	BlinkCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BlinkCollider"));
	BlinkCollider->InitCapsuleSize(42.0f, 96.0f);
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGauntletCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	//InputComponent->BindAction("Jump", IE_Pressed, this, &AGauntletCharacter::Blink);
	//InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &AGauntletCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AGauntletCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//InputComponent->BindAxis("TurnRate", this, &ATestCharacter::TurnAtRate);
	//InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//InputComponent->BindAxis("LookUpRate", this, &ATestCharacter::LookUpAtRate);

	// handle touch devices
	//InputComponent->BindTouch(IE_Pressed, this, &ATestCharacter::TouchStarted);
	//InputComponent->BindTouch(IE_Released, this, &ATestCharacter::TouchStopped);
}


void AGauntletCharacter::Tick(float Delta)
{
	Super::Tick(Delta);

	if (Controller != NULL)
	{
		APlayerController* PlayerController = (APlayerController*) GetWorld()->GetFirstPlayerController();
		
		FVector MouseLocation, MouseDirection;
		PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

		// Calculate the final rotation.
		FRotator ActorRotation		= GetActorRotation();
		FVector	 ActorLocation		= GetActorLocation() - (FVector::UpVector) * GetCapsuleComponent()->GetScaledCapsuleHalfHeight(); // Make sure the pivot point is at the actors feet.

		FVector  IntersectionPoint	= FMath::LinePlaneIntersection(MouseLocation, MouseLocation + MouseDirection, ActorLocation, FVector(0.0f, 0.0f, 1.0f));
		FRotator LookAtRotation		= FRotationMatrix::MakeFromX(IntersectionPoint - ActorLocation).Rotator();

		FRotator FinalRotation		= FRotator(ActorRotation.Pitch, LookAtRotation.Yaw, ActorRotation.Roll);

		SetActorRotation(FinalRotation);
	}
}


void AGauntletCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void AGauntletCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void AGauntletCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGauntletCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGauntletCharacter::MoveForward(float Value)
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

void AGauntletCharacter::MoveRight(float Value)
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

void AGauntletCharacter::Blink()
{
	static float BlinkLenght = 500.0f;

	FRotator Rotation = GetActorRotation();
	Rotation.Normalize();
	FVector Location = GetActorLocation();
	FHitResult TestHit;

	BlinkCollider->SetWorldLocation(Location + Rotation.Vector() * BlinkLenght, true, &TestHit);

	TArray<AActor*> Actors;
	BlinkCollider->GetOverlappingActors(Actors);

	
	if (Actors.Num() <= 0)
	{
		FHitResult MoveHit;
		SetActorLocation(Location + Rotation.Vector() * BlinkLenght, false, &MoveHit);
	}
}