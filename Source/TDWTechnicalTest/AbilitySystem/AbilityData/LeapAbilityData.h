// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoEAbilityData.h"
#include "LeapAbilityData.generated.h"

/** */
USTRUCT(BlueprintType)
struct FLeapAbiltiyKnockbackData
{
	GENERATED_BODY()

	/** */
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat PushRadius = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat KnockbackStrength = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat UpwardRatio = FScalableFloat();
};

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API ULeapAbilityData : public UAoEAbilityData
{
	GENERATED_BODY()

	/** */
	UPROPERTY(EditDefaultsOnly, Category="LeapAbility")
	FScalableFloat MinLeapDistance = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, Category="LeapAbility")
	FScalableFloat MaxArcHeight = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, Category="LeapAbility")
	FScalableFloat LeapBaseDuration = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, Category="LeapAbility")
	FLeapAbiltiyKnockbackData KnockbackData = FLeapAbiltiyKnockbackData();
};
