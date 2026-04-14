// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/IConsoleManager.h"
#include "DebugCVarsLibrary.generated.h"

/** Allows tracing debug of abilities (if they implement this CVar usage) */
extern TAutoConsoleVariable<int32> CVarDebugTraceAbility;

/**
* BP library that allows CVars to be used in BPs/cpp. These should be used
* as variables to be used in console for debugging.
*/
UCLASS()
class TDWTECHNICALTEST_API UDebugCVarsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Checks if abilities should debug its traces.
	*
	* @return True if abilities should debug its traces.
	*/
	UFUNCTION(BlueprintPure, Category = "Debug|CVar")
	static bool IsTraceAbilityDebugEnabled();
};
