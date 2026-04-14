// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataFragment_StatusEffect.h"
#include "AbilityDataFragment_Stun.generated.h"

/*
* Adds stun data to an ability data. Overrides the status effect to determine
* new rules of application, as well as adding the GE to the target using a set
* by caller logic, overriding the stun duration according to designer-defined
* duration on this fragment.
*/
UCLASS(BlueprintType)
class TDWTECHNICALTEST_API UAbilityDataFragment_Stun :
	public UAbilityDataFragment_StatusEffect
{
	GENERATED_BODY()

public:
	virtual bool ShouldApply(
		TObjectPtr<class UTDWTestGameplayAbility> Ability,
		TObjectPtr<class UAbilitySystemComponent> TargetASC) const
		override;

	virtual void Apply(TObjectPtr<class UTDWTestGameplayAbility> Ability,
		TObjectPtr<class UAbilitySystemComponent> TargetASC) const override;
	
public:
	UPROPERTY(EditDefaultsOnly)
	bool bFullHealthStunGuaranteed = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat Duration = FScalableFloat();
};
