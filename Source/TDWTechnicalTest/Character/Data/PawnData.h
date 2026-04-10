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
