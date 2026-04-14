// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDWTechnicalTestCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilitySystemComponentInitialized);

/**
* Base ACharacter class for project. Defines the delegate and health
* component, which should be used both by player and enemies. Any other
* character could also inherit from this base if these logic is needed.
*/
UCLASS(Blueprintable)
class ATDWTechnicalTestCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	/** Default constructor */
	ATDWTechnicalTestCharacterBase();

	/** Called every frame. */
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void SetupPlayerInputComponent(
		UInputComponent* PlayerInputComponent) override;

protected:
	/**
	* Should be called when the ASC has been initialized by the character.
	* 
	* Allows BP to do any initialization after the ASC. 
	*/
	UPROPERTY(BlueprintAssignable)
	FOnAbilitySystemComponentInitialized OnAbilitySystemComponentInitialized;

	/**
	* Simple health component that checks when character is dead.
	* 
	* The actual health/damage logic resides inside "UVitalsSet" (an attribute
	* set) modified by GEs.
	*/
	UPROPERTY()
	TObjectPtr<class UHealthComponent> HealthComponent;
};
