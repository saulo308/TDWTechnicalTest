// Copyright Saulo Soares. All rights reserved.

#include "DamageExecution.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestGameplayAbility.h"
#include "TDWTechnicalTest/AbilitySystem/AbilityData/AbilityDataBase.h"
#include "TDWTechnicalTest/AbilitySystem/Attributes/CombatSet.h"
#include "TDWTechnicalTest/AbilitySystem/Attributes/VitalsSet.h"

UDamageExecution::UDamageExecution()
{
	BaseDamageDef.AttributeToCapture = UCombatSet::GetBaseDamageAttribute();
	BaseDamageDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BaseDamageDef.bSnapshot = true;

	RelevantAttributesToCapture.Add(BaseDamageDef);
}

void UDamageExecution::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Get spec and ability to apply damage
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const auto* Ability = Cast<UTDWTestGameplayAbility>(
		Spec.GetContext().GetAbilityInstance_NotReplicated());
	if (!Ability)
	{
		return;
	}

	// Get the source base damage (I.e., ability owner base damage). We will
	// apply the ability's damage multiplier on top of it
	const auto* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const auto* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float BaseDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(BaseDamageDef,
		EvaluateParameters, BaseDamage);
	BaseDamage = FMath::Max(BaseDamage, 0.f);

	// Get the ability data to apply damage multiplier from the ability on top
	// of the base damage
	const UAbilityDataBase* AbilityData = Ability->GetAbilityData();
	if (!AbilityData)
	{
		return;
	}

	// Calculate the final damage multiplier using a random value between the
	// min/max set by designer
	const int32 AbilityLevel = Ability->GetAbilityLevel();
	const float MinDamageMultiplier =
		AbilityData->DamageMultiplier.MinMultiplier.GetValueAtLevel(AbilityLevel);
	const float MaxDamageMultiplier =
		AbilityData->DamageMultiplier.MaxMultiplier.GetValueAtLevel(AbilityLevel);
	const float FinalDamageMultiplier = FMath::FRandRange(MinDamageMultiplier,
		MaxDamageMultiplier);

	// Calculate the final damage (source base damage * ability damage
	// multiplier)
	float DamageDone = FMath::Max(BaseDamage * FinalDamageMultiplier, 0.f);
	if (DamageDone <= 0.f)
	{
		return;
	}

	TDWTestLog_ERROR(TEXT("%f"), DamageDone);
	
	// Apply the damage modifier, this gets turned into "-health" on the target
	// on "UVitalsSet"
	FGameplayModifierEvaluatedData ModifierData(
		UVitalsSet::GetDamageAttribute(), EGameplayModOp::Additive, DamageDone);
	OutExecutionOutput.AddOutputModifier(ModifierData);
}
