// Copyright Epic Games, Inc. All Rights Reserved.

#include "UETestCharacter.h"
#include "UETestProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "Components/ItemHandleComponent.h"
#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AUETestCharacter

AUETestCharacter::AUETestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create an ItemHandle
	ItemHandle = CreateDefaultSubobject<UItemHandleComponent>(TEXT("ItemHandle"));

	// Create an ArrowComponent
	ItemLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("ItemLocation"));
	ItemLocation->SetupAttachment(GetCapsuleComponent());
}

void AUETestCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	ItemHandle->Init(FirstPersonCameraComponent, ItemLocation);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AUETestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &AUETestCharacter::OnGrab);
	PlayerInputComponent->BindAction("Grab", IE_Released, this, &AUETestCharacter::Ungrab);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AUETestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUETestCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUETestCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUETestCharacter::LookUpAtRate);
}

void AUETestCharacter::OnGrab()
{
	ItemHandle->GrabItem();
}

void AUETestCharacter::Ungrab()
{
	ItemHandle->UngrabItem();
}

void AUETestCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AUETestCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AUETestCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUETestCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}