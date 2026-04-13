// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataFragment.h"
#include "ScalableFloat.h"
#include "AbilityDataFragment_ManaCost.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TDWTECHNICALTEST_API UAbilityDataFragment_ManaCost :
	public UAbilityDataFragment
{
	GENERATED_BODY()
	
public:
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat ManaCost = FScalableFloat();
};
