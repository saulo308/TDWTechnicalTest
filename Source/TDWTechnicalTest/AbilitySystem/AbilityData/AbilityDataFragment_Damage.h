// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataFragment.h"
#include "ScalableFloat.h"
#include "AbilityDataFragment_Damage.generated.h"

/** */
USTRUCT(BlueprintType)
struct FDamageCoefficientRange
{
	GENERATED_BODY()

	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat MinMultiplier = FScalableFloat();

	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat MaxMultiplier = FScalableFloat();
};

/**
 * 
 */
UCLASS(BlueprintType)
class TDWTECHNICALTEST_API UAbilityDataFragment_Damage :
	public UAbilityDataFragment
{
	GENERATED_BODY()
	
public:
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDamageCoefficientRange DamageMultiplier = FDamageCoefficientRange();
};
