// Copyright Saulo Soares. All rights reserved.

#include "TDWTechnicalTest/Input/Data/TDWTestInputConfig.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"

const UInputAction* UTDWTestInputConfig::FindNativeInputActionByTag(
	const FGameplayTag& InputTag, bool bLogNotFound/*=true*/) const
{
	// Find the desired input action by comparing the passed tag
	for (const FInputActionConfigData& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		TDWTestLog_ERROR(TEXT("Can't find NativeInputAction for InputTag "
			"[%s] on InputConfig [%s]."), *InputTag.ToString(), 
			*GetNameSafe(this));
	}

	return nullptr;
}
