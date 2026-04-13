// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataFragment.h"
#include "ScalableFloat.h"
#include "AbilityDataFragment_Leap.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TDWTECHNICALTEST_API UAbilityDataFragment_Leap :
	public UAbilityDataFragment
{
	GENERATED_BODY()
	
public:
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat MinLeapDistance = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat MaxLeapDistance = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat MaxArcHeight = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat LeapDuration = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCurveFloat> HorizontalCurve;
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCurveFloat> HeightCurve;
};
