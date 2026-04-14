// Copyright Saulo Soares. All rights reserved.


#include "DebugCVarsLibrary.h"

// Devs can use this console command to allow abilities trace debugging
TAutoConsoleVariable<int32> CVarDebugTraceAbility(
	TEXT("ability.Debug.TraceAbility"),
	0,
	TEXT("Enable debug traces inside Gameplay Abilities (0 = Off, 1 = On)"),
	ECVF_Default
);

bool UDebugCVarsLibrary::IsTraceAbilityDebugEnabled()
{
	return CVarDebugTraceAbility.GetValueOnGameThread() != 0;
}
