// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_AbilityCost.generated.h"

/**
* The MMC for ability cost calculation. This allows us to have a single GE for
* ability cost and let its value be set by the ability fragment of cost. Thus,
* designer don't need to create a GE for each GA, they just need to set the
* ability data to have a mana cost fragment and set the GE created for cost
* as the ability's GE cost.
*
* @note For now, this only applies to mana cost. But we could easily extend this
* to different types of cost, such as energy, health, etc.
*/
UCLASS()
class TDWTECHNICALTEST_API UMMC_AbilityCost :
	public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	/**
	* Calculates the magnitude to decrease from mana attribute on the target
	* the GE was applied to. This is used in conjunction of a GE that uses
	* this MMC as the magnitude calculation for decreasing mana from the
	* target.
	*
	* This allows us to get the mana cost of abilities from the ability data
	* fragment of mana cost, instead of relying on multiple GEs for GA cost.
	*/
	virtual float CalculateBaseMagnitude_Implementation(
		const FGameplayEffectSpec& Spec) const override;
};
