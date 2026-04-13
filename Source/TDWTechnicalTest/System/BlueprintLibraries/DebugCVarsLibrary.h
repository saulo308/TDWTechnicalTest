// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/IConsoleManager.h"
#include "DebugCVarsLibrary.generated.h"

extern TAutoConsoleVariable<int32> CVarDebugTraceAbility;

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API UDebugCVarsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Debug|CVar")
	static bool IsTraceAbilityDebugEnabled();
};
