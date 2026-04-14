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
* The default base GA for project.
*
* Every GA is composed of an UAbilityData, which contains designer-defined
* combat-like data that this ability can use when implemented.
*
* @note For this project, this is the base GA. For a broader project, this
* could be a specialization specifically for GAs that implement ARPG abilities,
* such as leap slam, lightning strike, power dash, etc.; while inheriting from
* an even more generic GA, that could handle other stuff. This GA specifically
* handles combat logic.
*/
UCLASS()
class TDWTECHNICALTEST_API UTDWTestGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	EAbilityActivationPolicy GetActivationPolicy() const
		{ return ActivationPolicy; }
	
	UFUNCTION(BlueprintCallable)
	class UAbilityDataBase* GetAbilityData() const { return AbilityData; }

	/**
	* Applies a radial knockback to characters given a character as source.
	*
	* @param Source The character that is originating the radial knockback.
	* @param Targets The targets to apply knockback to.
	* @param PushRadius The min distance between source and target to apply the
	* knockback.
	* @param KnockbackStrength The knockback's strength.
	* @param UpwardRatio How much of upward force should be applied in the
	* knockback
	*/
	UFUNCTION(BlueprintCallable)
	void ApplyRadialKnockbackToCharacters(ACharacter* Source,
		const TArray<AActor*>& Targets, float PushRadius,
		float KnockbackStrength, float UpwardRatio);
	
	/**
	* Helper function tha evaluates a FScalableFloat. The "GetValueAtLevel()" is
	* not exposed to BPs.
	*
	* @param ScalableFloat The scalable float to evaluate.
	*
	* @return The scalable float value at this ability's level.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats")
	float EvaluateScalableFloat(const FScalableFloat& ScalableFloat) const
		{ return ScalableFloat.GetValueAtLevel(GetAbilityLevel()); }
	
	/**
	* Applies an ability data fragment of type "status effect" on targets.
	* These fragments carry a GE to be applied, and may modify how the GE is
	* applied (and if) as they need.
	*
	* @param Targets The targets to apply the status effect
	* @param StatusEffectClass The ability fragment of type "status effect" to
	* apply on targets
	*/
	UFUNCTION(BlueprintCallable)
	void ApplyStatusEffectToTargets(const TArray<AActor*>& Targets,
		TSubclassOf<class UAbilityDataFragment_StatusEffect> StatusEffectClass);
	
public:
	/** Returns all tags that can put this ability into cooldown */
	virtual const FGameplayTagContainer* GetCooldownTags() const override;
	
	/**
	* Applies the cooldown GameplayEffect to the target. The duration is
	* calculated based on the ability's ability data cooldown fragment.
	*
	* This allows us to have a single cooldown GE, as we set its duration/tag
	* within this method. Thus, we don't need designers to create a cooldown GE
	* for each ability. They just need to set up the ability data using the
	* ability fragment cooldown!
	*/
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo) const override;
	
protected:
	/** Defines how this ability is meant to activate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		Category = "TDWTest|Ability Activation")
	EAbilityActivationPolicy ActivationPolicy =
		EAbilityActivationPolicy::OnInputTriggered;

private:
	/**
	* The ability's ability data. This contains all the data that "composes" the
	* data used by this ability. The ability data is composed of a number of
	* "ability data fragments", which allow designers to create/use ability data
	* without having to touch any cpp.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UAbilityDataBase> AbilityData;

	/**
	* Temp container that we will return the pointer to in GetCooldownTags().
	* This will be a union of our CooldownTags and the Cooldown GE's cooldown
	* tags.
	*/ 
	UPROPERTY(Transient)
	FGameplayTagContainer TempCooldownTags = FGameplayTagContainer();
};
