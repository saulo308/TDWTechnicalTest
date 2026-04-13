// Copyright Saulo Soares. All rights reserved.

#include "AbilityDataFragment_Stun.h"
#include "AbilitySystemComponent.h"
#include "TDWTechnicalTest/TDWTestTags.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestGameplayAbility.h"
#include "TDWTechnicalTest/AbilitySystem/Attributes/VitalsSet.h"

bool UAbilityDataFragment_Stun::ShouldApply(
	TObjectPtr<UTDWTestGameplayAbility> Ability,
	TObjectPtr<UAbilitySystemComponent> TargetASC) const
{
	const float Health = TargetASC->GetNumericAttribute(
		UVitalsSet::GetHealthAttribute());
	const float MaxHealth = TargetASC->GetNumericAttribute(
		UVitalsSet::GetMaxHealthAttribute());

	if (bFullHealthStunGuaranteed && Health >= MaxHealth)
	{
		return true;
	}

	return Super::ShouldApply(Ability, TargetASC);
}

void UAbilityDataFragment_Stun::Apply(
	TObjectPtr<UTDWTestGameplayAbility> Ability,
	TObjectPtr<UAbilitySystemComponent> TargetASC) const
{
	if (!Ability || !TargetASC || !EffectClass)
	{
		return;
	}
	
	const auto* SourceASC =	Ability->GetAbilitySystemComponentFromActorInfo();
	if (!SourceASC)
	{
		return;
	}

	// Create effect context to apply
	FGameplayEffectContextHandle Context = SourceASC->MakeEffectContext();
	Context.AddSourceObject(Ability);

	// Create the spec using the ability level
	FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(
		EffectClass, Ability->GetAbilityLevel(), Context);
	if (!SpecHandle.IsValid())
	{
		return;
	}

	// Set stun duration from scalable float based on the ability level
	const float StunDuration = Duration.GetValueAtLevel(
		Ability->GetAbilityLevel());
	SpecHandle.Data->SetSetByCallerMagnitude(TDWTestGameplayTags::AbilityStunTag,
		StunDuration);

	// Apply to target
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
