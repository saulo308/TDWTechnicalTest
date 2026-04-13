// Copyright Saulo Soares. All rights reserved.

#include "AbilityDataFragment_StatusEffect.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"

bool UAbilityDataFragment_StatusEffect::ShouldApply(
	TObjectPtr<UTDWTestGameplayAbility> Ability,
	TObjectPtr<UAbilitySystemComponent> TargetASC) const
{
	if (!Ability || !TargetASC)
	{
		return false;
	}

	const float Chance = ChanceToApply.GetValueAtLevel(
		Ability->GetAbilityLevel());
	return FMath::FRand() <= Chance;
}

void UAbilityDataFragment_StatusEffect::Apply(
	TObjectPtr<UTDWTestGameplayAbility> Ability,
	TObjectPtr<UAbilitySystemComponent> TargetASC) const
{
	if (!Ability || !TargetASC || !EffectClass)
	{
		return;
	}

	// Apply the status GE
	const auto* GameplayEffectCDO = EffectClass->GetDefaultObject<
		UGameplayEffect>();
	TargetASC->ApplyGameplayEffectToSelf(GameplayEffectCDO, 1,
		TargetASC->MakeEffectContext());
}
