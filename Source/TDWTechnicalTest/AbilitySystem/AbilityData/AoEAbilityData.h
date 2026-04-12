// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataBase.h"
#include "AoEAbilityData.generated.h"

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API UAoEAbilityData : public UAbilityDataBase
{
	GENERATED_BODY()
	
public:
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AoEAbility")
	FScalableFloat AoEDamageRadius = FScalableFloat();
};
