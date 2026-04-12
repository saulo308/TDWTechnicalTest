// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_RotateToLocation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotateToLocationDelegate);

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API UAbilityTask_RotateToLocation : public UAbilityTask
{
	GENERATED_BODY()

public:
	UAbilityTask_RotateToLocation();
	
public:
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
	UPROPERTY(BlueprintAssignable)
	FRotateToLocationDelegate OnFinished;

private:
	FVector TargetLocation = FVector();
	float SmoothTime = 0.f;
	TWeakObjectPtr<ACharacter> Character;
	bool bCanRotate = false;
};
