// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataFragment.h"
#include "ScalableFloat.h"
#include "GameplayTagContainer.h"
#include "AbilityDataFragment_Cooldown.generated.h"


/** Adds cooldown data to an ability data. */
UCLASS(BlueprintType)
class TDWTECHNICALTEST_API UAbilityDataFragment_Cooldown :
	public UAbilityDataFragment
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat CooldownDuration = FScalableFloat();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CooldownTag = FGameplayTag();
};
