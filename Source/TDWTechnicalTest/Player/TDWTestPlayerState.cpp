// Copyright Saulo Soares. All rights reserved.


#include "TDWTestPlayerState.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTechnicalTest/AbilitySystem/AbilitySet.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestAbilitySystemComponent.h"
#include "TDWTechnicalTest/Character/Data/PawnData.h"

ATDWTestPlayerState::ATDWTestPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<
		UTDWTestAbilitySystemComponent>(TEXT("AbilitySystem"));
}

UAbilitySystemComponent* ATDWTestPlayerState::GetAbilitySystemComponent()
	const
{
	return AbilitySystemComponent;
}

void ATDWTestPlayerState::SetPawnData(const TObjectPtr<UPawnData>& PawnData)
{
	if (!PawnData)
	{
		TDWTestLog_WARNING(TEXT("No pawn data was passed to player state."));
		return;
	}

	CurrentPawnData = PawnData;

	// Foreach ability set from pawn data, give it to the player's ASC
	for (const auto AbilitySet : PawnData->AbilitySets)
	{
		if (!AbilitySet)
		{
			continue;
		}
		
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
	}
}
