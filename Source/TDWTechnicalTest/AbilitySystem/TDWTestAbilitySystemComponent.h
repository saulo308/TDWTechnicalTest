// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TDWTestAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API UTDWTestAbilitySystemComponent :
	public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	/** */
	UTDWTestAbilitySystemComponent();
	
public:
	/** */
	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	
	/** */
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;

	/** */
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;
	
	/** */
	void ClearAbilityInput();

	/** */
	void AbilityInputTagPressed(const FGameplayTag& InputTag);

	/** */
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
protected:
	/** Handles to abilities that had their input pressed this frame. */
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	/** Handles to abilities that had their input released this frame. */
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

	/** Handles to abilities that have their input held. */
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
};
