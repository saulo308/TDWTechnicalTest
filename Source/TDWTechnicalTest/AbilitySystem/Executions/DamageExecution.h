// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecution.generated.h"

/**
* The GE execution calculation for damage. This allows us to calculate a
* dynamic value of damage to be applied by a GE. During calculation, we query
* the source's base damage and the source ability's damage fragment to scale the
* base damage. Finally, the calculation applies the damage through a meta
* attribute on the target's vitals attribute set.
*
* This allows us to have a single GE for damage, as we can calculate the
* damage to be applied dynamically with data assets.
*/
UCLASS()
class UDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UDamageExecution();

protected:
	/**
	* Calculates how much damage should be applied to the GE's target. The final
	* value will be the source's base damage scaled by the source ability's
	* damage multiplier (which comes from an ability data fragment).
	*
	* The final value will be applied to the target's damage meta attribute on
	* the vitals attribute set.
	*/
	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
		override;
	
private:
	/** The base damage to capture from source. */
	FGameplayEffectAttributeCaptureDefinition BaseDamageDef;
};
