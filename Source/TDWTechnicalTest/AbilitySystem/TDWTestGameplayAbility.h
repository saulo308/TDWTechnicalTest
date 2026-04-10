// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TDWTestGameplayAbility.generated.h"

/** Defines how an ability is meant to activate. */
UENUM(BlueprintType)
enum class EAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	OnSpawn
};

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API UTDWTestGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	/** */
	EAbilityActivationPolicy GetActivationPolicy() const
		{ return ActivationPolicy; }
	
protected:
	/** Defines how this ability is meant to activate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		Category = "TDWTest|Ability Activation")
	EAbilityActivationPolicy ActivationPolicy;
};
