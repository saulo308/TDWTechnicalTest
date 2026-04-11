// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ScalableFloat.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AbilityDataBase.generated.h"

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
	FScalableFloat Damage = FScalableFloat();
	
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
