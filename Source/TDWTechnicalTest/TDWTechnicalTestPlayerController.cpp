// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDWTechnicalTestPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"

ATDWTechnicalTestPlayerController::ATDWTechnicalTestPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATDWTechnicalTestPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATDWTechnicalTestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
