// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

/**
* Simple health component that checks when character is dead.
* 
* The actual health/damage logic resides inside "UVitalsSet" (an attribute set)
* modified by GEs.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDWTECHNICALTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/** Sets default values for this component's properties */
	UHealthComponent();

public:	
	/**
	* Initializes this component with an ASC. Will listen to its
	* "UVitalsSet" attribute set to know when owner is dead.
	*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	void InitializeWithAbilitySystem(class UAbilitySystemComponent* InASC);

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

	/**
	* Handles when owner is out of health. As a simple implementation, will
	* just destroy its owner.
	*/
	virtual void HandleOutOfHealth();

private:
	/** The bound attribute set that stores owner's health. */
	UPROPERTY()
	TObjectPtr<const class UVitalsSet> VitalsSet;
};
