// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "Engine/DataAsset.h"
#include "TDWTechnicalTest/Input/Data/TDWTestInputConfig.h"
#include "PawnData.generated.h"

/** */
UCLASS(BlueprintType, Const)
class TDWTECHNICALTEST_API UPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Ability sets to grant to this pawn's ability system. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TObjectPtr<class UAbilitySet>> AbilitySets;
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FInputMappingContextData> DefaultInputMappings;

	/**
	* Input configuration used by player controlled pawns to create input
	* mappings and bind input actions.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UTDWTestInputConfig> InputConfig;
};
