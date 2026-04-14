// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TDWTestAssetManager.generated.h"

/** Project asset manager. Initializes the AbilitySystem globals during load. */
UCLASS()
class TDWTECHNICALTEST_API UTDWTestAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	/**
	* Starts initial load, gets called from InitializeObjectReferences.
	* Initializes the ability system globals.
	*/
	virtual void StartInitialLoading() override;
};
