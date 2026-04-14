// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_RotateToLocation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotateToLocationDelegate);

/** Ability task that smoothly rotates the owning avatar to a given location. */
UCLASS()
class TDWTECHNICALTEST_API UAbilityTask_RotateToLocation : public UAbilityTask
{
	GENERATED_BODY()

public:
	UAbilityTask_RotateToLocation();
	
public:
	/** 
	* Smoothly interpolates the avatar's rotation to look at a given target
	* location.
	*
	* @param TargetLocation The location to look at.
	* @param SmoothTime How smooth the rotation should be.
	*/
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks",
		meta = (DisplayName="RotateCharacterToLocation",
		HidePin = "OwningAbility", DefaultToSelf = "OwningAbility",
		BlueprintInternalUseOnly = "true"))
	static UAbilityTask_RotateToLocation* RotateCharacterToLocation(
		UGameplayAbility* OwningAbility, FVector TargetLocation,
		float SmoothTime = 5.f);

public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;

public:
	/** Called when the rotation has finished. */
	UPROPERTY(BlueprintAssignable)
	FRotateToLocationDelegate OnFinished;

private:
	FVector TargetLocation = FVector();
	
	float SmoothTime = 0.f;
	
	TWeakObjectPtr<ACharacter> Character;
	
	bool bCanRotate = false;
};
