// Copyright Saulo Soares. All rights reserved.

#include "TDWTechnicalTestPlayerController.h"
#include "AbilitySystem/TDWTestAbilitySystemComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "Player/TDWTestPlayerState.h"

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

ATDWTestPlayerState* ATDWTechnicalTestPlayerController::GetTDWTestPlayerState()
	const
{
	return CastChecked<ATDWTestPlayerState>(PlayerState,
		ECastCheckedType::NullAllowed);
}

UTDWTestAbilitySystemComponent* ATDWTechnicalTestPlayerController::GetTDWTestAbilitySystemComponent()
	const
{
	const auto* TDWTestPlayerState = GetTDWTestPlayerState();
	return TDWTestPlayerState ?
		TDWTestPlayerState->GetTDWTestAbilitySystemComponent() :
		nullptr;
}

void ATDWTechnicalTestPlayerController::PostProcessInput(const float DeltaTime,
	const bool bGamePaused)
{
	if (auto* TDWTestASC = GetTDWTestAbilitySystemComponent())
	{
		TDWTestASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}
