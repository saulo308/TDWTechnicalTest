// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDWTechnicalTestCharacterBase.h"

ATDWTechnicalTestCharacterBase::ATDWTechnicalTestCharacterBase()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATDWTechnicalTestCharacterBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ATDWTechnicalTestCharacterBase::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
