// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecution.generated.h"

/** */
UCLASS()
class UDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

protected:
	/** */
	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
		override;
};
