// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilitySet.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestGameplayAbility.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestAbilitySystemComponent.h"

void FAbilitySet_GrantedHandles::AddAbilitySpecHandle(
	const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void FAbilitySet_GrantedHandles::AddGameplayEffectHandle(
	const FActiveGameplayEffectHandle& Handle)
{
	if (Handle.IsValid())
	{
		GameplayEffectHandles.Add(Handle);
	}
}

void FAbilitySet_GrantedHandles::AddAttributeSet(UAttributeSet* Set)
{
	GrantedAttributeSets.Add(Set);
}

void FAbilitySet_GrantedHandles::TakeFromAbilitySystem(
	UAbilitySystemComponent* TargetASC)
{
	if(!TargetASC)
	{
		TDWTestLog_ERROR(TEXT("Can't take ability set to invalid ASC."));
		return;	
	}

	// The game is singleplayer, but just to be safe here...
	if (!TargetASC->IsOwnerActorAuthoritative())
	{
		TDWTestLog_ERROR(TEXT("AbilitySets must only be removed from "
			"server. Failed to remove ability set."));
		return;
	}

	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			TargetASC->ClearAbility(Handle);
		}
	}

	for (const FActiveGameplayEffectHandle& Handle : GameplayEffectHandles)
	{
		if (Handle.IsValid())
		{
			TargetASC->RemoveActiveGameplayEffect(Handle);
		}
	}

	for (UAttributeSet* Set : GrantedAttributeSets)
	{
		TargetASC->RemoveSpawnedAttribute(Set);
	}

	AbilitySpecHandles.Reset();
	GameplayEffectHandles.Reset();
	GrantedAttributeSets.Reset();
}

void UAbilitySet::GiveToAbilitySystem(
	UAbilitySystemComponent* TargetASC,
	FAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const
{
	if(!TargetASC)
	{
		TDWTestLog_ERROR(TEXT("Can't give ability set to invalid ASC."));
		return;	
	}
	
	// The game is singleplayer, but just to be safe here...
	if (!TargetASC->IsOwnerActorAuthoritative())
	{
		TDWTestLog_ERROR(TEXT("AbilitySets must only be granted from "
			"server. Failed to give [%s] ability set."), *GetName());
		return;
	}

	// Grant the gameplay abilities from the ability set
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num();
		++AbilityIndex)
	{
		// Get the ability to grant
		const auto& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];
		if (!IsValid(AbilityToGrant.Ability))
		{
			TDWTestLog_ERROR(TEXT("GrantedGameplayAbilities [%d] on ability "
				"set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}

		auto* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<
			UTDWTestGameplayAbility>();

		// Create the ability spec, passing the source objet and tags
		FGameplayAbilitySpec AbilitySpec(AbilityCDO,
			AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityToGrant.InputTag);

		// Give the ability to ASC
		const auto AbilitySpecHandle = TargetASC->GiveAbility(AbilitySpec);
		
		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}

	// Grant the attribute sets from the ability set.
	for (int32 SetIndex = 0; SetIndex < GrantedAttributes.Num(); ++SetIndex)
	{
		const auto& SetToGrant = GrantedAttributes[SetIndex];
		if (!IsValid(SetToGrant.AttributeSet))
		{
			TDWTestLog_ERROR(TEXT("GrantedAttributes[%d] on ability set "
				"[%s] is not valid"), SetIndex, *GetNameSafe(this));
			continue;
		}

		// Add the attribute set
		auto* NewSet = NewObject<UAttributeSet>(TargetASC->GetOwner(),
			SetToGrant.AttributeSet);
		TargetASC->AddAttributeSetSubobject(NewSet);

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAttributeSet(NewSet);
		}
	}

	// Grant the gameplay effects from ability set.
	for (int32 EffectIndex = 0; EffectIndex < GrantedGameplayEffects.Num();
		++EffectIndex)
	{
		const auto& EffectToGrant =	GrantedGameplayEffects[EffectIndex];
		if (!IsValid(EffectToGrant.GameplayEffect))
		{
			TDWTestLog_ERROR(TEXT("GrantedGameplayEffects[%d] on ability set "
				"[%s] is not valid"), EffectIndex, *GetNameSafe(this));
			continue;
		}

		// Apply the GE
		const auto* GameplayEffect = EffectToGrant.GameplayEffect->
			GetDefaultObject<UGameplayEffect>();
		const FActiveGameplayEffectHandle GameplayEffectHandle =
			TargetASC->ApplyGameplayEffectToSelf(GameplayEffect,
			EffectToGrant.EffectLevel, TargetASC->MakeEffectContext());

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddGameplayEffectHandle(GameplayEffectHandle);
		}
	}
}
