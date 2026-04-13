// Copyright Saulo Soares. All rights reserved.

#include "TDWTestAssetManager.h"
#include "AbilitySystemGlobals.h"


void UTDWTestAssetManager::StartInitialLoading() 
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
