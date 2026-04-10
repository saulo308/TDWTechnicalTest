// Copyright Saulo Soares. All rights reserved.


#include "TDWTestPlayerState.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestAbilitySystemComponent.h"

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
