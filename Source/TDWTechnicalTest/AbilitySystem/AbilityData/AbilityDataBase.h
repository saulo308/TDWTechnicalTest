// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AbilityDataBase.generated.h"

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API UAbilityDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** */
	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType="FragmentClass"))
	const class UAbilityDataFragment* FindFragmentByClass(
		TSubclassOf<class UAbilityDataFragment> FragmentClass) const;
	
public:
	/** */
	template<typename T>
	const T* FindFragment() const
		{ return Cast<T>(FindFragmentByClass(T::StaticClass())); }
	
public:
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityUniqueId = FGameplayTag();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TArray<TObjectPtr<class UAbilityDataFragment>> AbilityFragments;
};
