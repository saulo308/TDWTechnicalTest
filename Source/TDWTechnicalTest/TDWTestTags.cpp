// Copyright Saulo Soares. All rights reserved.

#include "TDWTestTags.h"

namespace TDWTestGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Move, "InputTag.Move", "Move input.");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AbilityCooldownTag, "Data.Cooldown", "Cooldown GE tag to set cooldown duration with \"SetByCaller\".");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(LeapMovementState, "State.Movement.Leaping", "Movement state indicating the character is leaping;");
}
