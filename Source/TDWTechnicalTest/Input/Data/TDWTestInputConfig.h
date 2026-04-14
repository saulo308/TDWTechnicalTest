// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TDWTestInputConfig.generated.h"

/** Stores data for IMC registering. */
USTRUCT(BlueprintType)
struct FInputMappingContextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<class UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere)
	int32 Priority = 0;
};

/**
* Allows binding input tags to input actions. When this input action is bound
* to the custom enhanced input component, its callback will receive the
* defined input tag. Thus, this allows us to bind an input action to a given
* FGameplayTag.
*
* This same input tag can be used to activate/send input press/released events
* to GAs, as we can also "bind" GAs to tags.
*
* Note that (@see UAbilitySet) contains information to bind a GA to an input
* tag, which should match this input config input tag.
*/
USTRUCT(BlueprintType)
struct FInputActionConfigData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const class UInputAction> InputAction;
};

/**
* Contains a list of native and ability actions. Can be used as a set of inputs.
*
* Mainly used to initialize character inputs.
*	1. Ability Actions: Input actions bound to abilities (GAs).
*	2. Native Actions: Any other action, like move, jump, look, etc.
*/
UCLASS()
class TDWTECHNICALTEST_API UTDWTestInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	const UInputAction* FindNativeInputActionByTag(
		const FGameplayTag& InputTag, bool bLogNotFound = true) const;

public:
	/**
	* List of input actions used by the owner. These input actions are mapped
	* to a gameplay tag and must be manually bound.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FInputActionConfigData> NativeInputActions;

	/**
	* List of input actions used by the owner. These input actions are mapped
	* to a gameplay tag and are automatically bound to abilities with matching
	* input tags.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FInputActionConfigData> AbilityInputActions;
};
