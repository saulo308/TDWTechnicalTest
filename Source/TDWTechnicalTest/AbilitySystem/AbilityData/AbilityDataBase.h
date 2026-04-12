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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat MinMultiplier = FScalableFloat();

	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Base|Stats")
	FDamageCoefficientRange DamageMultiplier = FDamageCoefficientRange();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Base|Stats")
	FScalableFloat ManaCost = FScalableFloat();

	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Base|Cooldown")
	FScalableFloat CooldownDuration = FScalableFloat();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Base|Cooldown")
	FGameplayTag CooldownTag = FGameplayTag();
};
