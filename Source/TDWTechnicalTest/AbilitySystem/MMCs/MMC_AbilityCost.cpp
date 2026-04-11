// Copyright Saulo Soares. All rights reserved.


#include "MMC_AbilityCost.h"
#include "Abilities/GameplayAbility.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestGameplayAbility.h"
#include "TDWTechnicalTest/AbilitySystem/AbilityData/AbilityDataBase.h"

float UMMC_AbilityCost::CalculateBaseMagnitude_Implementation(
	const FGameplayEffectSpec& Spec) const
{
	const auto* Ability = Cast<UTDWTestGameplayAbility>(
		Spec.GetContext().GetAbilityInstance_NotReplicated());
	if (!Ability)
	{
		return 0.f;
	}

	const auto* AbilityData = Ability->GetAbilityData();
	if (!AbilityData)
	{
		return 0.f;
	}

	const float ManaCost = AbilityData->ManaCost.GetValueAtLevel(
		Ability->GetAbilityLevel());

	// Negative because cost subtracts mana. We could also do this in the GE
	// setup.
	return -ManaCost;
}
