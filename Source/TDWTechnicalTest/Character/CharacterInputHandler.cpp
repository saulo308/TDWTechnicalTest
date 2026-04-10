// Copyright Saulo Soares. All rights reserved.


#include "CharacterInputHandler.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "TDWTechnicalTest/TDWTestTags.h"
#include "TDWTechnicalTest/Input/TDWTestInputComponent.h"

UCharacterInputHandler::UCharacterInputHandler()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterInputHandler::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterInputHandler::InitializePlayerInput(
	TObjectPtr<UInputComponent> InputComponent)
{
	OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		TDWTestLog_ERROR(TEXT("Expected character input handler to be "
			"used by a pawn. Owner is [%s]."), *GetOwner()->GetName());
		return;
	}
	
	// Get the owner's player controller, so we can add IMCs
	OwnerPlayerController = OwnerPawn->GetController<APlayerController>();
	check(OwnerPlayerController);
	
	// Register all the default IMCs
	if (!RegisterDefaultInputMappingContexts())
	{
		return;
	}

	// Register all native actions
	RegisterNativeActions(InputComponent);
	
	TDWTestLog_INFO(TEXT("Character [%s] input initialized."),
		*GetOwner()->GetName());
}

bool UCharacterInputHandler::RegisterDefaultInputMappingContexts()
{
	if(!OwnerPlayerController)
	{
		TDWTestLog_ERROR(TEXT("Can't register IMC with invalid player "
			"controller from [%s]."), *GetOwner()->GetName());
		return false;
	}
	
	const auto LocalPlayer = OwnerPlayerController->GetLocalPlayer();
	check(LocalPlayer);

	const auto EnhancedInputSubsystem = LocalPlayer->GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>();
	check(EnhancedInputSubsystem);

	// For each default IMC, register it to the subsystem
	for (const auto& IMCData : CharacterDefaultInputMappings)
	{
		EnhancedInputSubsystem->AddMappingContext(
			IMCData.InputMapping.LoadSynchronous(), IMCData.Priority);
	}
	
	return true;
}

void UCharacterInputHandler::RegisterNativeActions(
	const TObjectPtr<UInputComponent>& InputComponent)
{
	if (!CharacterInputConfig)
	{
		return;
	}
	
	// Get the input component, so we can bind the native actions
	const auto EnhancedInputComponent = Cast<UTDWTestInputComponent>(
		InputComponent);
	check(EnhancedInputComponent);

	// Bind the move action
	EnhancedInputComponent->BindNativeAction(CharacterInputConfig,
		TDWTestGameplayTags::InputTag_Move, ETriggerEvent::Triggered,
		this, &UCharacterInputHandler::Input_Move, true);
}

void UCharacterInputHandler::Input_Move(
	const FInputActionValue& InputActionValue)
{
	check(OwnerPawn);

	// Get the input value
	const FVector2D Value = InputActionValue.Get<FVector2D>();
	if (Value.IsNearlyZero())
	{
		return;
	}

	// Calculate movement direction
	const FRotator ControlRotation = OwnerPawn->GetControlRotation();
	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Add movement
	OwnerPawn->AddMovementInput(Forward, Value.Y);
	OwnerPawn->AddMovementInput(Right, Value.X);
}
