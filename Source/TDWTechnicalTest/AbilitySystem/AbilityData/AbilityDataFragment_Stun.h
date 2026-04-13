// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataFragment_StatusEffect.h"
#include "AbilityDataFragment_Stun.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TDWTECHNICALTEST_API UAbilityDataFragment_Stun :
	public UAbilityDataFragment_StatusEffect
{
	GENERATED_BODY()

public:
	/** */
	virtual bool ShouldApply(
		TObjectPtr<class UTDWTestGameplayAbility> Ability,
		TObjectPtr<class UAbilitySystemComponent> TargetASC) const
		override;

	/** Applies the gameplay effect */
	virtual void Apply(TObjectPtr<class UTDWTestGameplayAbility> Ability,
		TObjectPtr<class UAbilitySystemComponent> TargetASC) const override;
	
public:
	/** */
	UPROPERTY(EditDefaultsOnly)
	bool bFullHealthStunGuaranteed = true;
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat Duration = FScalableFloat();
};
