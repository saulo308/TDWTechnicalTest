// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TDWTestInputConfig.generated.h"

/**
* 
*/
USTRUCT()
struct FInputMappingContextData
{
	GENERATED_BODY()

	/** */
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<class UInputMappingContext> InputMapping;

	/**
	* Higher priority input mappings will be prioritized over mappings with a
	* lower priority.
	*/
	UPROPERTY(EditAnywhere)
	int32 Priority = 0;
};

/**
* 
*/
USTRUCT(BlueprintType)
struct FInputActionConfigData
{
	GENERATED_BODY()

	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();
	
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const class UInputAction> InputAction;
};

/**
* 
*/
UCLASS()
class TDWTECHNICALTEST_API UTDWTestInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/** */
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
