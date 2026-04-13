// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataFragment.h"
#include "ScalableFloat.h"
#include "AbilityDataFragment_StatusEffect.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TDWTECHNICALTEST_API UAbilityDataFragment_StatusEffect :
	public UAbilityDataFragment
{
	GENERATED_BODY()
	
public:
	/** Determines if the effect should be applied */
	virtual bool ShouldApply(
		TObjectPtr<class UTDWTestGameplayAbility> Ability,
		TObjectPtr<class UAbilitySystemComponent> TargetASC) const;

	/** Applies the gameplay effect */
	virtual void Apply(TObjectPtr<class UTDWTestGameplayAbility> Ability,
		TObjectPtr<class UAbilitySystemComponent> TargetASC) const;
	
public:
	/** Gameplay effect that will be applied if the roll succeeds */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> EffectClass;

	/** Base chance to apply the effect */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat ChanceToApply = 1.0f;
};
