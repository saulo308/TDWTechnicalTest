// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CombatStaticsLibrary.generated.h"

/**
 * 
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
	*/
	UFUNCTION(BlueprintCallable, Category="Combat")
	static void ApplyRadialKnockback(ACharacter* Source, ACharacter* Target,
		float LaunchStrength, float UpwardRatio = 0.5f);

	/**
	* Computes the knockback launch velocity without applying it.
	*/
	UFUNCTION(BlueprintCallable, Category="Combat")
	static FVector ComputeKnockbackVelocity(const FVector& SourceLocation,
		const FVector& TargetLocation, float LaunchStrength,
		float UpwardRatio = 0.5f);
};
