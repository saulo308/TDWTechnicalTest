// Copyright Saulo Soares. All rights reserved.

#include "DamageExecution.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestGameplayAbility.h"
#include "TDWTechnicalTest/AbilitySystem/AbilityData/AbilityDataBase.h"
#include "TDWTechnicalTest/AbilitySystem/AbilityData/AbilityDataFragment_Damage.h"
#include "TDWTechnicalTest/AbilitySystem/Attributes/CombatSet.h"
#include "TDWTechnicalTest/AbilitySystem/Attributes/VitalsSet.h"

UDamageExecution::UDamageExecution()
{
	// Capture source base damage attribute to scale with ability's damage
	// multiplier
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

	// Get the damage fragment, so we can use the damage data set by designer
	const auto DamageAbilityData = AbilityData->FindFragment<
		UAbilityDataFragment_Damage>();
	if (!DamageAbilityData)
	{
		TDWTestLog_ERROR(TEXT("No damage  set on ability [%s]. Damage will not "
			"be applied."), *GetNameSafe(this));
		return;
	}
	
	// Calculate the final damage multiplier using a random value between the
	// min/max set by designer
	const int32 AbilityLevel = Ability->GetAbilityLevel();
	const float MinDamageMultiplier = DamageAbilityData->DamageMultiplier.
		MinMultiplier.GetValueAtLevel(AbilityLevel);
	const float MaxDamageMultiplier = DamageAbilityData->DamageMultiplier.
		MaxMultiplier.GetValueAtLevel(AbilityLevel);
	const float FinalDamageMultiplier = FMath::FRandRange(MinDamageMultiplier,
		MaxDamageMultiplier);

	// Calculate the final damage (source base damage * ability damage
	// multiplier)
	float DamageDone = FMath::Max(BaseDamage * FinalDamageMultiplier, 0.f);
	if (DamageDone <= 0.f)
	{
		return;
	}

	// Apply the damage modifier, this gets turned into "-health" on the target
	// on "UVitalsSet"
	FGameplayModifierEvaluatedData ModifierData(
		UVitalsSet::GetDamageAttribute(), EGameplayModOp::Additive, DamageDone);
	OutExecutionOutput.AddOutputModifier(ModifierData);
}
