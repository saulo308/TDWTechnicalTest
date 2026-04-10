// Copyright Saulo Soares. All rights reserved.


#include "TDWTestAbilitySystemComponent.h"
#include "TDWTestGameplayAbility.h"


UTDWTestAbilitySystemComponent::UTDWTestAbilitySystemComponent()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}

void UTDWTestAbilitySystemComponent::AbilitySpecInputPressed(
	FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);

	// We don't support UGameplayAbility::bReplicateInputDirectly.
	// Use replicated events instead so that the WaitInputPress ability task
	// works.
	if (Spec.IsActive())
	{
PRAGMA_DISABLE_DEPRECATION_WARNINGS
		const UGameplayAbility* Instance = Spec.GetPrimaryInstance();
		FPredictionKey OriginalPredictionKey = Instance ?
			Instance->GetCurrentActivationInfo().GetActivationPredictionKey() :
			Spec.ActivationInfo.GetActivationPredictionKey();
PRAGMA_ENABLE_DEPRECATION_WARNINGS
		
		// Invoke the InputPressed event. This is not replicated here. If
		// someone is listening, they may replicate the InputPressed event to
		// the server.
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed,
			Spec.Handle, OriginalPredictionKey);
	}
}

void UTDWTestAbilitySystemComponent::AbilitySpecInputReleased(
	FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputReleased(Spec);

	// We don't support UGameplayAbility::bReplicateInputDirectly.
	// Use replicated events instead so that the WaitInputRelease ability task
	// works.
	if (Spec.IsActive())
	{
PRAGMA_DISABLE_DEPRECATION_WARNINGS
		const UGameplayAbility* Instance = Spec.GetPrimaryInstance();
		FPredictionKey OriginalPredictionKey = Instance ?
			Instance->GetCurrentActivationInfo().GetActivationPredictionKey() :
			Spec.ActivationInfo.GetActivationPredictionKey();
PRAGMA_ENABLE_DEPRECATION_WARNINGS

		// Invoke the InputReleased event. This is not replicated here. If
		// someone is listening, they may replicate the InputReleased event to
		// the server.
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased,
			Spec.Handle, OriginalPredictionKey);
	}
}

void UTDWTestAbilitySystemComponent::AbilityInputTagPressed(
	const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}
	
	for (const auto& AbilitySpec : ActivatableAbilities.Items)
	{
		if (AbilitySpec.Ability && (AbilitySpec.GetDynamicSpecSourceTags().
			HasTagExact(InputTag)))
		{
			InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
			InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
		}
	}
}

void UTDWTestAbilitySystemComponent::AbilityInputTagReleased(
	const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}
	
	for (const auto& AbilitySpec : ActivatableAbilities.Items)
	{
		if (AbilitySpec.Ability && (AbilitySpec.GetDynamicSpecSourceTags().
			HasTagExact(InputTag)))
		{
			InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
			InputHeldSpecHandles.Remove(AbilitySpec.Handle);
		}
	}
}

void UTDWTestAbilitySystemComponent::ProcessAbilityInput(float DeltaTime,
	bool bGamePaused)
{
	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();
	
	// Process all abilities that activate when the input is held.
	for (const auto& SpecHandle : InputHeldSpecHandles)
	{
		const auto* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle);
		if (!AbilitySpec)
		{
			continue;
		}
		
		if (AbilitySpec->Ability && !AbilitySpec->IsActive())
		{
			const auto* AbilityCDO = Cast<UTDWTestGameplayAbility>(
				AbilitySpec->Ability);
			if (AbilityCDO && AbilityCDO->GetActivationPolicy() ==
				EAbilityActivationPolicy::WhileInputActive)
			{
				AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
			}
		}
	}

	// Process all abilities that had their input pressed this frame.
	for (const auto& SpecHandle : InputPressedSpecHandles)
	{
		auto* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle);
		if (!AbilitySpec)
		{
			continue;
		}
		
		if (!AbilitySpec->Ability)
		{
			continue;
		}
		
		AbilitySpec->InputPressed = true;

		if (AbilitySpec->IsActive())
		{
			// Ability is active so pass along the input event.
			AbilitySpecInputPressed(*AbilitySpec);
		}
		else
		{
			const auto* AbilityCDO = Cast<UTDWTestGameplayAbility>(
				AbilitySpec->Ability);
			if (AbilityCDO && AbilityCDO->GetActivationPolicy() ==
				EAbilityActivationPolicy::OnInputTriggered)
			{
				AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
			}
		}
	}

	// Try to activate all the abilities that are from presses and holds.
	// We do it all at once so that held inputs don't activate the ability
	// and then also send an input event to the ability because of the press.
	for (const auto& AbilitySpecHandle : AbilitiesToActivate)
	{
		TryActivateAbility(AbilitySpecHandle);
	}

	// Process all abilities that had their input released this frame.
	for (const auto& SpecHandle : InputReleasedSpecHandles)
	{
		auto* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle);
		if (!AbilitySpec)
		{
			continue;
		}
		if (!AbilitySpec->Ability)
		{
			continue;
		}
		
		AbilitySpec->InputPressed = false;
		if (AbilitySpec->IsActive())
		{
			// Ability is active so pass along the input event.
			AbilitySpecInputReleased(*AbilitySpec);
		}
	}

	// Clear the cached ability handles.
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void UTDWTestAbilitySystemComponent::ClearAbilityInput()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}
