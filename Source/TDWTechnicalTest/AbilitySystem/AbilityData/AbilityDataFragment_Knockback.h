// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataFragment.h"
#include "ScalableFloat.h"
#include "AbilityDataFragment_Knockback.generated.h"


/** Adds knockback data to an ability data. */
UCLASS(BlueprintType)
class TDWTECHNICALTEST_API UAbilityDataFragment_Knockback :
	public UAbilityDataFragment
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat PushRadius = FScalableFloat();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat KnockbackStrength = FScalableFloat();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat UpwardRatio = FScalableFloat();
};
