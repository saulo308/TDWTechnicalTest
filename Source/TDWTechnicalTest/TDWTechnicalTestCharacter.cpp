// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDWTechnicalTestCharacter.h"
#include "TWDTechnicalTestLogging.h"
#include "AbilitySystem/TDWTestAbilitySystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Character/CharacterInputHandler.h"
#include "Character/Data/PawnData.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Player/TDWTestPlayerState.h"

ATDWTechnicalTestCharacter::ATDWTechnicalTestCharacter()
{
	InputHandler = CreateDefaultSubobject<UCharacterInputHandler>(
		TEXT("InputHandler"));
	
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATDWTechnicalTestCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ATDWTechnicalTestCharacter::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Load the default pawn data, so we can bind input
	if (const auto LoadedPawnData = DefaultPawnData.LoadSynchronous())
	{
		// Initialize the input handler with the player input component
		check(InputHandler);
		InputHandler->InitializePlayerInput(PlayerInputComponent,
			LoadedPawnData);
	}
}

void ATDWTechnicalTestCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitAbilitySystemComponent();

	// Set pawn data on player state, so it can give the player's AbilitySets.
	// This is safe to do here, as now the ASC is initialized
	if (const auto LoadedPawnData = DefaultPawnData.LoadSynchronous())
	{
		const auto TDWTestPlayerState = Cast<ATDWTestPlayerState>(
			GetPlayerState());
		check(TDWTestPlayerState);
		TDWTestPlayerState->SetPawnData(LoadedPawnData);
	}

	OnAbilitySystemComponentInitialized.Broadcast();
}

void ATDWTechnicalTestCharacter::InitAbilitySystemComponent()
{
	// Get the AbilitySystemComponent on the player state
	const auto TDWPlayerState = GetPlayerState<ATDWTestPlayerState>();

	// Check if the player state is valid
	if(!TDWPlayerState)
	{
		TDWTestLog_ERROR(TEXT("Can't init character [%s] ASC with invalid "
			"player state."), *GetName());
		return;
	}

	// Get the player state ability system component
	AbilitySystemComponent =
		TDWPlayerState->GetTDWTestAbilitySystemComponent();
	check(AbilitySystemComponent);

	// Init the ability actor info
	AbilitySystemComponent->InitAbilityActorInfo(TDWPlayerState, this);
	
	TDWTestLog_INFO(TEXT("Initialized character [%s] ASC."), *GetName());
}

UAbilitySystemComponent* ATDWTechnicalTestCharacter::GetAbilitySystemComponent()
	const
{
	return AbilitySystemComponent;
}
