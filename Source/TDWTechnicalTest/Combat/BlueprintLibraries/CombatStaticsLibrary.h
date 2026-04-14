// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CombatStaticsLibrary.generated.h"

/**
* Simple BP library that implements helper functions for combat. Currently,
* implements knockback auxiliary functions that may be called by GAs.
*/
UCLASS()
class TDWTECHNICALTEST_API UCombatStaticsLibrary :
	public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Applies a radial knockback from Source to Target.
	* Target will be launched away from the source with an upward arc.
	*
	* @param Source The source target that is applying knockback (also used as
	* knockback origin).
	* @param Target The target to be launched by knockback force.
	* @param LaunchStrength The knockback strength.
	* @param UpwardRatio How much the knockback should knock the target in air
	*/
	UFUNCTION(BlueprintCallable, Category="Combat")
	static void ApplyRadialKnockback(ACharacter* Source, ACharacter* Target,
		float LaunchStrength, float UpwardRatio = 0.5f);

	/**
	* Computes the knockback launch velocity without applying it. I.e.,
	* calculates the direction for knockback.
	*
	* @param SourceLocation The source location that is applying knockback.
	* @param TargetLocation The target location that will be launched by
	* knockback force.
	* @param LaunchStrength The knockback strength.
	* @param UpwardRatio How much the knockback should knock the target in air
	*/
	UFUNCTION(BlueprintCallable, Category="Combat")
	static FVector ComputeKnockbackVelocity(const FVector& SourceLocation,
		const FVector& TargetLocation, float LaunchStrength,
		float UpwardRatio = 0.5f);
};
