// Copyright Saulo Soares. All rights reserved.

#include "DamageExecution.h"
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
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const auto* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const auto* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float BaseDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		BaseDamageDef, EvaluateParameters, BaseDamage);
	
	const float DamageDone = FMath::Max(BaseDamage, 0.0f);
	if (DamageDone == 0.0f)
	{
		return;
	}
	
	// Apply a damage modifier, this gets turned into "-health" on the target
	// on "UVitalsSet"
	FGameplayModifierEvaluatedData ModifierData(
		UVitalsSet::GetDamageAttribute(), EGameplayModOp::Additive, DamageDone);
	OutExecutionOutput.AddOutputModifier(ModifierData);
}
