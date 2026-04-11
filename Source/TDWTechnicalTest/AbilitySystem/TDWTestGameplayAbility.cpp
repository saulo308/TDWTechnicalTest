// Copyright Saulo Soares. All rights reserved.

#include "TDWTestGameplayAbility.h"
#include "AbilityData/AbilityDataBase.h"
#include "TDWTechnicalTest/TDWTestTags.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"

const FGameplayTagContainer* UTDWTestGameplayAbility::GetCooldownTags() const
{
	if (!AbilityData)
	{
		return Super::GetCooldownTags();
	}
	
	// MutableTags writes to the TempCooldownTags on the CDO so clear it in case
	// the ability cooldown tags change (moved to a different slot)
	auto* MutableTags = const_cast<FGameplayTagContainer*>(&TempCooldownTags);
	MutableTags->Reset();

	// Append the parent cooldown tags (if any)
	if (const auto* ParentTags = Super::GetCooldownTags())
	{
		MutableTags->AppendTags(*ParentTags);
	}

	// Also append designer-defined cooldown tag, as we will add these tags
	// through the cooldown GE
	MutableTags->AddTag(AbilityData->CooldownTag);
	return MutableTags;
}

void UTDWTestGameplayAbility::ApplyCooldown(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo) const
{
	const auto* CooldownGE = GetCooldownGameplayEffect();
	if (!CooldownGE)
	{
		return;
	}

	if (!AbilityData)
	{
		TDWTestLog_ERROR(TEXT("No AbilityData set on ability [%s]. Cooldown "
			"will not be applied."), *GetNameSafe(this));
		return;
	}

	// Create the GE handle, so we can apply our ability duration
	auto SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownGE->GetClass(),
		GetAbilityLevel());
	
	// Add the cooldown tag to the GE
	SpecHandle.Data.Get()->DynamicGrantedTags.AddTag(AbilityData->CooldownTag);
	
	// Set the duration defined by designer on the GE
	const float CooldownDuration =
		AbilityData->CooldownDuration.GetValueAtLevel(GetAbilityLevel());
	SpecHandle.Data.Get()->SetSetByCallerMagnitude(
		TDWTestGameplayTags::AbilityCooldownTag, CooldownDuration);
	
	// Apply the cooldown GE
	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo,
		SpecHandle);
}
