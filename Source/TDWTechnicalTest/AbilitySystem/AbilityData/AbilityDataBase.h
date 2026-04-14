// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AbilityDataBase.generated.h"

/**
* The base data for abilities. An ability base is the data asset that we pass
* to GAs with data they can use in implementation.
*
* For a data-driven architecture implementation, the ability data is composed
* of multiple "ability data fragments". Each fragment defines a different data
* that the ability data can have. For instance, an ability data can have the
* fragments of damage, cooldown, mana cost, stun, etc. This data can be used
* in the GAs implementation as the designer pleases.
*
* This architecture allows designers to create data assets from this ability
* data class and only configure fragments for them. We don't really need to
* create any other data asset in .cpp for specific abilities. For instance,
* "ULeapSlamAbilityData" (X). All ability data could come directly from this
* base class.
*
* This architecture would also allow us to go crazy and even implement generic
* GAs for ability types. For instance, instead of having a "GA_LeapSlam", we
* could have a "GA_Leap". The final behavior of this GA would be determined by
* the fragments added to its ability data. As a result, we could have a leap
* slam, a leap shield, leap only for movement (no damage), leap without
* mana cost, etc.; all using a single GA implementation. The GA itself would
* only need to check if the ability data has a given fragment to decide if it
* should or shouldn't do something (e.g., apply damage on landed). Thus, the
* final behavior would be completely in hands of the designer, which could
* create a handful of abilities with a single GA implementation.
*/
UCLASS()
class TDWTECHNICALTEST_API UAbilityDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/**
	* Finds an ability data fragment by its class on this ability data.
	*
	* @param FragmentClass The fragment class to bind on this ability data.
	*
	* @return The ability data fragment set on this ability data. May return
	* nullptr if not found.
	*/
	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType="FragmentClass"))
	const class UAbilityDataFragment* FindFragmentByClass(
		TSubclassOf<class UAbilityDataFragment> FragmentClass) const;
	
public:
	/** Templated version of find fragment by class. Syntax sugar. */
	template<typename T>
	const T* FindFragment() const
		{ return Cast<T>(FindFragmentByClass(T::StaticClass())); }
	
public:
	/** The id to identify the ability. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityUniqueId = FGameplayTag();
	
	/**
	* The fragments that composes this ability data.
	*
	* @note They are instanced objects, so no need to create the fragments
	* on editor content browser.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TArray<TObjectPtr<class UAbilityDataFragment>> AbilityFragments;
};
