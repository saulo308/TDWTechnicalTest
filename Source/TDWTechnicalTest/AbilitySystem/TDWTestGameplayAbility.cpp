// Copyright Saulo Soares. All rights reserved.

#include "TDWTestGameplayAbility.h"
#include "AbilityData/AbilityDataBase.h"
#include "AbilityData/AbilityDataFragment_Cooldown.h"
#include "GameFramework/Character.h"
#include "TDWTechnicalTest/TDWTestTags.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTechnicalTest/Combat/BlueprintLibraries/CombatStaticsLibrary.h"

const FGameplayTagContainer* UTDWTestGameplayAbility::GetCooldownTags() const
{
	if (!AbilityData)
	{
		return Super::GetCooldownTags();
	}
	
	const auto CooldownAbilityData = AbilityData->FindFragment<
		UAbilityDataFragment_Cooldown>();
	if (!CooldownAbilityData)
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
	MutableTags->AddTag(CooldownAbilityData->CooldownTag);
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

	// Get the cooldown fragment, so we can use the cooldown data set by
	// designer
	const auto CooldownAbilityData = AbilityData->FindFragment<
		UAbilityDataFragment_Cooldown>();
	if (!CooldownAbilityData)
	{
		TDWTestLog_ERROR(TEXT("No cooldown fragment set on ability [%s]. "
			"Cooldown will not be applied."), *GetNameSafe(this));
		return;
	}
	
	// Create the GE handle, so we can apply our ability duration
	auto SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownGE->GetClass(),
		GetAbilityLevel());

	// Add the cooldown tag to the GE
	SpecHandle.Data.Get()->DynamicGrantedTags.AddTag(
		CooldownAbilityData->CooldownTag);
	
	// Set the duration defined by designer on the GE
	const float CooldownDuration = CooldownAbilityData->CooldownDuration.
		GetValueAtLevel(GetAbilityLevel());
	SpecHandle.Data.Get()->SetSetByCallerMagnitude(
		TDWTestGameplayTags::AbilityCooldownTag, CooldownDuration);
	
	// Apply the cooldown GE
	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo,
		SpecHandle);
}

void UTDWTestGameplayAbility::ApplyRadialKnockbackToCharacters(
	ACharacter* Source, const TArray<AActor*>& Targets, float PushRadius,
	float KnockbackStrength, float UpwardRatio)
{
	if (!Source)
	{
		TDWTestLog_ERROR(TEXT("Can't apply radial knockback with invalid "
			"source."));
		return;	
	}
	
	const auto SourceLocation = Source->GetActorLocation();
	for (auto* Target : Targets)
	{
		if (!Target || !Cast<ACharacter>(Target))
		{
			continue;
		}

		// Check if the target is within knockback distance. If not, ignore
		const float DistSq = FVector::DistSquared2D(Target->GetActorLocation(),
			SourceLocation);
		if (DistSq > PushRadius * PushRadius)
		{
			continue;
		}

		UCombatStaticsLibrary::ApplyRadialKnockback(Source,
			Cast<ACharacter>(Target), KnockbackStrength, UpwardRatio);
	}
}
