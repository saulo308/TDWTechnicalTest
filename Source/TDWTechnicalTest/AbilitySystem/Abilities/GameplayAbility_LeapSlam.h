// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestGameplayAbility.h"
#include "GameplayAbility_LeapSlam.generated.h"

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API UGameplayAbility_LeapSlam :
	public UTDWTestGameplayAbility
{
	GENERATED_BODY()

public:
	/** */
	UFUNCTION(BlueprintCallable)
	void StartTargeting(float AoERadius, bool bDebugTrace);

	/** */
	UFUNCTION(BlueprintImplementableEvent)
	void OnTargetDataReady(const FGameplayAbilityTargetDataHandle& TargetData);
	
private:
	/** */
	FGameplayAbilityTargetDataHandle BuildTargetDataFromActors(
		const TArray<AActor*>& Actors);
};
