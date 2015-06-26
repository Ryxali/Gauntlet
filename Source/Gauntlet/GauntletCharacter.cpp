// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Gauntlet.h"
#include "Engine.h"
#include <math.h>
#include "GauntletCharacter.h"

//////////////////////////////////////////////////////////////////////////
// AGauntletCharacter

AGauntletCharacter::AGauntletCharacter() : MouseInputCache(), LookDir(1.0f, 0.0f, 0.0f), TumbleDir(FVector::ZeroVector)
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
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	AngleTweak = GetMesh()->RelativeRotation;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGauntletCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	//InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AGauntletCharacter::InitTumble);

	InputComponent->BindAxis("MoveForward", this, &AGauntletCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AGauntletCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//InputComponent->BindAxis("TurnRate", this, &AGauntletCharacter::TurnAtRate);
	//InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//InputComponent->BindAxis("LookUpRate", this, &AGauntletCharacter::LookUpAtRate);

	InputComponent->BindAxis("Turn", this, &AGauntletCharacter::HorizontalInput);
	InputComponent->BindAxis("TurnRate", this, &AGauntletCharacter::HorizontalInputRate);
	InputComponent->BindAxis("LookUp", this, &AGauntletCharacter::VerticalInput);
	InputComponent->BindAxis("LookUpRate", this, &AGauntletCharacter::VerticalInputRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &AGauntletCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AGauntletCharacter::TouchStopped);
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
	//AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGauntletCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	//AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
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
	if ( (Controller != NULL) && (Value != 0.0f) )
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

void AGauntletCharacter::Tick(float Delta)
{
	FVector f = GetLastMovementInputVector();
	if (!f.IsNearlyZero()){
		TumbleDir = f;
	}
	LookDir += MouseInputCache;
	LookDir.Z = 0;
	if (LookDir.SizeSquared() > 0.0f)
	{
		LookDir = LookDir.GetUnsafeNormal();
	}
	else
	{
		LookDir = FVector(1.0f, 0.0f, 0.0f);
	}
	//FVector::DotProduct(FVector(1.0f, 0.0f, 0.0f), LookDir);
	float euls = FMath::RadiansToDegrees(atan2(LookDir.Y, LookDir.X));//FVector::DotProduct(LookDir, FVector::ForwardVector);//LookDir.CosineAngle2D(FVector::ForwardVector);
	FRotator r = FRotator::MakeFromEuler(FVector(0.0f, 0.0f, euls + AngleTweak.Euler().Z));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(euls));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, r.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, LookDir.ToString());
	MouseInputCache = FVector::ZeroVector;
	GetMesh()->RelativeRotation = r;
}

void AGauntletCharacter::VerticalInput(float Delta)
{
	MouseInputCache.Y += Delta;
}
void AGauntletCharacter::VerticalInputRate(float Rate)
{
	VerticalInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
void AGauntletCharacter::HorizontalInput(float Delta)
{
	MouseInputCache.X += Delta;
}
void AGauntletCharacter::HorizontalInputRate(float Rate)
{
	HorizontalInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGauntletCharacter::InitTumble() 
{
	//AngleTweak.RotateVector(GetMesh()->GetRightVector())
	Tumble(TumbleDir);
}