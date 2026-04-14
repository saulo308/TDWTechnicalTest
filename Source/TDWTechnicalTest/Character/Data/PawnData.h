// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "Engine/DataAsset.h"
#include "TDWTechnicalTest/Input/Data/TDWTestInputConfig.h"
#include "PawnData.generated.h"

/**
* The pawn data contains information on abilities, attributes and gameplay
* effects to apply to the pawn; as well as input config. Can be seen as
* abilities, attributes and GEs to give to the pawn that sets this data.
*
* The pawn data will also be used to initialize player input for player
* controlled pawns.
*
* @see UAbilitySet
*/
UCLASS(BlueprintType, Const)
class TDWTECHNICALTEST_API UPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Ability sets to grant to this pawn's ability system. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TObjectPtr<class UAbilitySet>> AbilitySets;
	
	/** The pawn's default IMCs. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FInputMappingContextData> DefaultInputMappings;

	/**
	* Input configuration used by player controlled pawns to create input
	* mappings and bind input actions.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UTDWTestInputConfig> InputConfig;
};
