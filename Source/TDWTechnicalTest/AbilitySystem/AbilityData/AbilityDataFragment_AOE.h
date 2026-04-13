// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataFragment.h"
#include "ScalableFloat.h"
#include "AbilityDataFragment_AOE.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TDWTECHNICALTEST_API UAbilityDataFragment_AOE :
	public UAbilityDataFragment
{
	GENERATED_BODY()
	
public:
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AoEAbility")
	FScalableFloat AoEDamageRadius = FScalableFloat();
};
