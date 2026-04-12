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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat PushRadius = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat KnockbackStrength = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat UpwardRatio = FScalableFloat();
};

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API ULeapAbilityData : public UAoEAbilityData
{
	GENERATED_BODY()

public:
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="LeapAbility")
	FScalableFloat MinLeapDistance = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="LeapAbility")
	FScalableFloat MaxLeapDistance = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="LeapAbility")
	FScalableFloat MaxArcHeight = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="LeapAbility")
	FScalableFloat LeapBaseDuration = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="LeapAbility")
	FLeapAbiltiyKnockbackData KnockbackData = FLeapAbiltiyKnockbackData();
};
