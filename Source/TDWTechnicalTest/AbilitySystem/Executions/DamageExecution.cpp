// Copyright Saulo Soares. All rights reserved.

#include "DamageExecution.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestGameplayAbility.h"
#include "TDWTechnicalTest/AbilitySystem/AbilityData/AbilityDataBase.h"
#include "TDWTechnicalTest/AbilitySystem/Attributes/VitalsSet.h"

void UDamageExecution::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Get the ability context from the spec
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const auto* Ability = Cast<UTDWTestGameplayAbility>(
		Spec.GetContext().GetAbilityInstance_NotReplicated());
	if (!Ability)
	{
		return;
	}

	// Try to find the ability data, so we can access the ability's damage
	const auto* AbilityData = Ability->GetAbilityData();
	if (!AbilityData)
	{
		return;
	}

	// Set the damage to be applied
	const float Damage = AbilityData->Damage.GetValueAtLevel(
		Ability->GetAbilityLevel());
	
	const float DamageDone = FMath::Max(Damage, 0.0f);
	if (DamageDone <= 0.f)
	{
		return;
	}

	// Output damage
	const FGameplayModifierEvaluatedData ModifierData(
		UVitalsSet::GetDamageAttribute(), EGameplayModOp::Additive, DamageDone);
	OutExecutionOutput.AddOutputModifier(ModifierData);
}
