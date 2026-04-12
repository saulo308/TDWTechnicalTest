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
	UFUNCTION(BlueprintCallable)
	EAbilityActivationPolicy GetActivationPolicy() const
		{ return ActivationPolicy; }
	
	/** */
	UFUNCTION(BlueprintCallable)
	class UAbilityDataBase* GetAbilityData() const { return AbilityData; }

	/** */
	UFUNCTION(BlueprintCallable)
	void ApplyRadialKnockbackToCharacters(ACharacter* Source,
		const TArray<AActor*>& Targets, float PushRadius,
		float KnockbackStrength, float UpwardRatio);
	
public:
	/** Returns all tags that can put this ability into cooldown */
	virtual const FGameplayTagContainer* GetCooldownTags() const override;
	
	/** Applies CooldownGameplayEffect to the target */
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
	/** */
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
