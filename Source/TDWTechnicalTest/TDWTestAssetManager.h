// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TDWTestAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API UTDWTestAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	/** Starts initial load, gets called from InitializeObjectReferences */
	virtual void StartInitialLoading() override;
};
