// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "NativeGameplayTags.h"

/**
* List of tags used in Cpp and also in BP. Here is easier and more safe to
* declare, as they will be added automatically to project (see .cpp).
*/
namespace TDWTestGameplayTags
{
	TDWTECHNICALTEST_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	
	TDWTECHNICALTEST_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AbilityCooldownTag);
	TDWTECHNICALTEST_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AbilityStunTag);
	
	TDWTECHNICALTEST_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(LeapMovementState);
	TDWTECHNICALTEST_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(StunMovementState);
}
