// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestGameplayAbility.h"
#include "GameplayAbility_LeapSlam.generated.h"

/** The leap slam GA base implementation. */
UCLASS()
class TDWTECHNICALTEST_API UGameplayAbility_LeapSlam :
	public UTDWTestGameplayAbility
{
	GENERATED_BODY()

public:
	/**
	* Starts targeting enemies within an AOE radius. Will call
	* "OnTargetDataReady()" after finding the enemies in range and the target
	* data has been created.
	*
	* @param AoERadius The radius to target enemies.
	* @param bDebugTrace Indicates if we should debug the AOE Radius.
	*/
	UFUNCTION(BlueprintCallable)
	void StartTargeting(float AoERadius, bool bDebugTrace);

	/**
	* Called when we've found enemies within targeting radius. Lets BP
	* handle the logic on found enemies.
	*
	* @param TargetData The target data created with found enemies during
	* targeting.
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void OnTargetDataReady(const FGameplayAbilityTargetDataHandle& TargetData);
	
private:
	FGameplayAbilityTargetDataHandle BuildTargetDataFromActors(
		const TArray<AActor*>& Actors);
};
