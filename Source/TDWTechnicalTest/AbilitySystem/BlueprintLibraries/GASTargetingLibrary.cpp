// Copyright Saulo Soares. All rights reserved.


#include "GASTargetingLibrary.h"

#include "NavigationSystem.h"
#include "Engine/OverlapResult.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"

void UGASTargetingLibrary::GetActorsInRadius(UWorld* World,
	const FVector& Origin, float Radius,
	const TArray<TEnumAsByte<ECollisionChannel>>& ObjectTypes,
	bool bDebugTrace, TArray<AActor*>& OutActors, AActor* IgnoreActor/*=nullptr*/)
{
	if (!World)
	{
		return;
	}

	// Make sphere for sphere overlap
	TArray<FOverlapResult> Overlaps;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(IgnoreActor);

	// Add collision channels to overlap
	FCollisionObjectQueryParams ObjectQuery;
	for (ECollisionChannel Channel : ObjectTypes)
	{
		ObjectQuery.AddObjectTypesToQuery(Channel);
	}

	if (bDebugTrace)
	{
		DrawDebugSphere(World, Origin, Radius, 32, FColor::Green, false, 2.0f);
	}
	
	// Find actors in range
	World->OverlapMultiByObjectType(Overlaps, Origin, FQuat::Identity,
		ObjectQuery, Sphere,Params);

	// Add to return
	for (const auto& Result : Overlaps)
	{
		if (auto* Actor = Result.GetActor())
		{
			OutActors.AddUnique(Actor);
		}
	}
}

FLeapTargetResult UGASTargetingLibrary::CalculateLeapTarget(
	UObject* WorldContextObject, const APlayerController* PlayerController,
	const FVector& Origin, float MaxDistance, float MaxHeight)
{
	if (!WorldContextObject)
	{
		TDWTestLog_ERROR(TEXT("Can't calculate leap target with invalid "
			"world context."));
		return FLeapTargetResult();
	}
	
	if (!PlayerController)
	{
		TDWTestLog_ERROR(TEXT("Can't calculate leap target with invalid "
			"player controller."));
		return FLeapTargetResult();
	}
	
	// Get the mouse position, so we can get its world location
	float MousePositionX = 0.f;
	float MousePositionY = 0.f;
	PlayerController->GetMousePosition(MousePositionX, MousePositionY);

	// Project the current mouse position to world, so we can know where player
	// desires to leap
	FVector MouseWorldPosition =  FVector();
	FVector MouseWorldDirection = FVector();
	if (!PlayerController->DeprojectScreenPositionToWorld(MousePositionX,
			MousePositionY,	MouseWorldPosition, MouseWorldDirection))
	{
		TDWTestLog_ERROR(TEXT("Error while deprojecting mouse position to "
			"world. Failed to find leap target."));
		return FLeapTargetResult();
	}

	// Calculate an intersection between the mouse world location with a plane.
	// This will allow us to get the mouse world location "on ground"
	FVector LinePlaneIntersectionStart = MouseWorldPosition;
	FVector LinePlaneIntersectionEnd = MouseWorldPosition +
		(MouseWorldDirection * 100000.f);
	float T = 0.f;
	FVector Intersection = FVector();
	if (!UKismetMathLibrary::LinePlaneIntersection_OriginNormal(
		LinePlaneIntersectionStart, LinePlaneIntersectionEnd, Origin,
		FVector::UpVector, T, Intersection))
	{
		TDWTestLog_ERROR(TEXT("Couldn't find plane intersection between mouse "
			"and origin. Failed to find leap target."));
		return FLeapTargetResult();
	}

	// Now that we have the mouse world location "on ground" try to get such
	// location as a "navigable" point. This will allow us to correct any
	// location that the character can't reach, given the leap max distance
	auto* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(
		WorldContextObject);
	FNavLocation ProjectedIntersectionOnNav = FNavLocation();
	const FVector Extent = FVector(MaxDistance, MaxDistance, MaxHeight);
	if (!NavSys->ProjectPointToNavigation(Intersection,
		ProjectedIntersectionOnNav, Extent))
	{
		// If we fail to find a point on navigation, we may have been way of
		// a navigation point (e.g., mouse over the abyss). To try to correct
		// that, let's try to shorten the leap target by getting the direction
		// the player desires to leap * max leap distance

		// Get the desired leap direction and multiply it by the max leap
		// distance
		FVector DesiredLeapDirection = Intersection - Origin;
		DesiredLeapDirection.Normalize();
		FVector NewIntersection = Origin + (DesiredLeapDirection * MaxDistance);

		// Once that is done, try to recalculate a point in navigation that we
		// can leap to
		if (!NavSys->ProjectPointToNavigation(NewIntersection,
			ProjectedIntersectionOnNav, Extent))
		{
			return FLeapTargetResult();
		}

		// If found, then we can leap there. This way, we correct any attempt
		// to leap towards the abyss by getting the furthest possible
		// (navigable) leap distance on that direction
		FVector DesiredLeapLocation = ProjectedIntersectionOnNav.Location;
		return FLeapTargetResult(DesiredLeapLocation, true);
	}

	// --- We've found a location to leap towards on navigation, where player
	// was desiring
	FVector DesiredLeapLocation = ProjectedIntersectionOnNav.Location;

	// Clamp such location by using a **square rectangle** from origin
	FVector DeltaLocation = DesiredLeapLocation - Origin;
	DeltaLocation.X = FMath::Clamp(DeltaLocation.X, -MaxDistance, MaxDistance);
	DeltaLocation.Y = FMath::Clamp(DeltaLocation.Y, -MaxDistance, MaxDistance);

	// Recalculate the clamped location, keeping the desired leap location Z,
	// as we may be going up or down during leap
	FVector ClampedLeapLocation = Origin + DeltaLocation;
	ClampedLeapLocation.Z = DesiredLeapLocation.Z;

	// If clamped location is already inside bounds, then we can just return it
	if (ClampedLeapLocation == DesiredLeapLocation)
	{
		return FLeapTargetResult(ClampedLeapLocation, true);
	}

	// --- If not in bounds, lets recalculate the Z position, as the new clamped
	// position may not be the same as the desired Z. E.g., the player has mouse
	// over a higher ground, but the leap was clamped to the same Z that the
	// origin is currently in.
	// This way, we will trace to find the correct (new clamped location) Z
	FVector LineStart = ClampedLeapLocation + FVector(0.f, 0.f, MaxHeight);
	FVector LineEnd = ClampedLeapLocation - FVector(0.f, 0.f, MaxHeight);
	ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	TArray<AActor*> ActorsToIgnore;
	FHitResult OutHit;
	UKismetSystemLibrary::LineTraceSingle(WorldContextObject, LineStart,
		LineEnd, TraceType, false, ActorsToIgnore, EDrawDebugTrace::None,
		OutHit, true);

	if (!OutHit.bBlockingHit)
	{
		return FLeapTargetResult();
	}

	return FLeapTargetResult(OutHit.Location, true);
}
