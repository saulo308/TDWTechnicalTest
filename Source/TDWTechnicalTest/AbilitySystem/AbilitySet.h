// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "ActiveGameplayEffectHandle.h"
#include "Engine/DataAsset.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpecHandle.h"
#include "AbilitySet.generated.h"

/**	Data used by the ability set to grant gameplay abilities. */
USTRUCT(BlueprintType)
struct FAbilitySet_GameplayAbility
{
	GENERATED_BODY()

	/** Gameplay ability to grant. */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTDWTestGameplayAbility> Ability;

	/** Level of ability to grant. */
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	/** Tag used to process input for the ability. */
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag = FGameplayTag();
};

/** Data used by the ability set to grant gameplay effects. */
USTRUCT(BlueprintType)
struct FAbilitySet_GameplayEffect
{
	GENERATED_BODY()

	/** Gameplay effect to grant. */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> GameplayEffect = nullptr;

	/** Level of gameplay effect to grant. */
	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};

/** Data used by the ability set to grant attribute sets. */
USTRUCT(BlueprintType)
struct FAbilitySet_AttributeSet
{
	GENERATED_BODY()

	/** Gameplay effect to grant. */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeSet> AttributeSet;
};

/** Data used to store handles to what has been granted by the ability set. */
USTRUCT(BlueprintType)
struct FAbilitySet_GrantedHandles
{
	GENERATED_BODY()

	/** */
	void TakeFromAbilitySystem(class UAbilitySystemComponent* TargetASC);
	
	/** */
	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	
	/** */
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
	
	/** */
	void AddAttributeSet(UAttributeSet* Set);

protected:
	/** Handles to the granted abilities. */
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	/** Handles to the granted gameplay effects. */
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	/** Pointers to the granted attribute sets. */
	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;
};


/**
* Non-mutable data asset used to grant gameplay abilities and gameplay effects.
*/
UCLASS(BlueprintType, Const)
class UAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/**
	* Grants the ability set to the specified ability system component.
	* 
	* The returned handles can be used later to take away anything that was
	* granted.
	*/ 
	void GiveToAbilitySystem(class UAbilitySystemComponent* TargetASC,
		FAbilitySet_GrantedHandles* OutGrantedHandles,
		UObject* SourceObject = nullptr) const;

protected:
	/** Gameplay abilities to grant when this ability set is granted. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TArray<FAbilitySet_GameplayAbility> GrantedGameplayAbilities;

	/** Gameplay effects to grant when this ability set is granted. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<FAbilitySet_GameplayEffect> GrantedGameplayEffects;

	/** Attribute sets to grant when this ability set is granted. */
	UPROPERTY(EditDefaultsOnly, Category = "Attribute Sets")
	TArray<FAbilitySet_AttributeSet> GrantedAttributes;
};
