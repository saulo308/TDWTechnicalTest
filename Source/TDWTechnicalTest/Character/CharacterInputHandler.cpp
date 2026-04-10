// Copyright Saulo Soares. All rights reserved.


#include "CharacterInputHandler.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

UCharacterInputHandler::UCharacterInputHandler()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterInputHandler::BeginPlay()
{
	Super::BeginPlay();

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
}

void UCharacterInputHandler::InitializePlayerInput(
	TObjectPtr<UInputComponent> InputComponent)
{
	TDWTestLog_INFO(TEXT("Initializing character [%s] input."),
		*GetOwner()->GetName());

	// Register all the default IMCs
	RegisterDefaultInputMappingContexts();
}

void UCharacterInputHandler::RegisterDefaultInputMappingContexts()
{
	if(!OwnerPlayerController)
	{
		return;
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
}
