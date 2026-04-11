// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ScalableFloat.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AbilityDataBase.generated.h"

/** */
USTRUCT(BlueprintType)
struct FDamageCoefficientRange
{
	GENERATED_BODY()

	/** */
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat MinMultiplier = FScalableFloat();

	/** */
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat MaxMultiplier = FScalableFloat();
};

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API UAbilityDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** */
	UPROPERTY(EditDefaultsOnly, Category="Base|Stats")
	FDamageCoefficientRange DamageMultiplier = FDamageCoefficientRange();
	
	/** */
	UPROPERTY(EditDefaultsOnly, Category="Base|Stats")
	FScalableFloat ManaCost = FScalableFloat();

	/** */
	UPROPERTY(EditDefaultsOnly, Category="Base|Cooldown")
	FScalableFloat CooldownDuration = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, Category = "Base|Cooldown")
	FGameplayTag CooldownTag = FGameplayTag();
};
