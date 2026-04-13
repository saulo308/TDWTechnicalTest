// Copyright Saulo Soares. All rights reserved.


#include "MMC_AbilityCost.h"
#include "Abilities/GameplayAbility.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestGameplayAbility.h"
#include "TDWTechnicalTest/AbilitySystem/AbilityData/AbilityDataBase.h"
#include "TDWTechnicalTest/AbilitySystem/AbilityData/AbilityDataFragment_ManaCost.h"

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

	// Get the mana cost fragment, so we can use the mana cost data set by
	// designer
	const auto ManaCostAbilityData = AbilityData->FindFragment<
		UAbilityDataFragment_ManaCost>();
	if (!ManaCostAbilityData)
	{
		TDWTestLog_ERROR(TEXT("No mana cost fragment set on ability [%s]. "
			"Cost will not be applied."), *GetNameSafe(this));
		return 0.f;
	}
	
	const float ManaCost = ManaCostAbilityData->ManaCost.GetValueAtLevel(
		Ability->GetAbilityLevel());

	// Negative because cost subtracts mana. We could also do this in the GE
	// setup.
	return -ManaCost;
}
