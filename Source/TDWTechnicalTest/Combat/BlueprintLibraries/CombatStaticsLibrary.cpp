// Copyright Saulo Soares. All rights reserved.


#include "CombatStaticsLibrary.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

void UCombatStaticsLibrary::ApplyRadialKnockback(ACharacter* Source,
	ACharacter* Target, float LaunchStrength, float UpwardRatio)
{
	if (!Source || !Target)
	{
		return;
	}

	// Compute the knockback velocity for the character
	const FVector LaunchVelocity = ComputeKnockbackVelocity(
		Source->GetActorLocation(), Target->GetActorLocation(),
		LaunchStrength, UpwardRatio);

	// Apply knockback
	Target->LaunchCharacter(LaunchVelocity, true, true);
}

FVector UCombatStaticsLibrary::ComputeKnockbackVelocity(
	const FVector& SourceLocation, const FVector& TargetLocation,
	float LaunchStrength, float UpwardRatio)
{
	// Calculate the knockback direction relative to source
	FVector Direction = TargetLocation - SourceLocation;

	// Ignore vertical difference for radial push
	Direction.Z = 0.f;

	if (!Direction.Normalize())
	{
		// Fallback in case both actors are in almost same location
		Direction = FVector::ForwardVector;
	}

	const FVector LaunchVector = Direction + FVector::UpVector * UpwardRatio;
	return LaunchVector.GetSafeNormal() * LaunchStrength;
}
