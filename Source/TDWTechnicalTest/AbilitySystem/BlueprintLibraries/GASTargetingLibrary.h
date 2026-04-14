// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASTargetingLibrary.generated.h"

/**
* Stores the data for a calculated leap target location. Used as return from
* leap target calculation.
*/
USTRUCT(BlueprintType)
struct FLeapTargetResult
{

	GENERATED_BODY()

public:
	/** The location to leap */
	UPROPERTY(BlueprintReadOnly)
	FVector Location = FVector();
	
	/** Indicates if the location was successfully calculated. */
	UPROPERTY(BlueprintReadOnly)
	bool bIsValid = false;
};

/**
* Helper library to calculate any targeting logic. For now, implements helper
* methods to get actors in a radius and calculate leap target locations.
*/
UCLASS()
class TDWTECHNICALTEST_API UGASTargetingLibrary :
	public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Gets all actors in a given radius using a given set of collision
	* channels.
	*
	* @param World World context object for trace.
	* @param Origin The origin to get the actors from.
	* @param Radius The radius from origin to get actors.
	* @param ObjectTypes The types of objects to get.
	* @param bDebugTrace Indicates if we should debug this operation
	* @param OutActors The list of actors found within radius.
	* @param IgnoreActor The actor to be ignored by this operation.
	*/
	UFUNCTION(BlueprintCallable, Category="GASTargeting")
	static void GetActorsInRadius(UWorld* World, const FVector& Origin,
		float Radius, const TArray<TEnumAsByte<ECollisionChannel>>& ObjectTypes,
		bool bDebugTrace, TArray<AActor*>& OutActors,
		AActor* IgnoreActor = nullptr);
	
	/**
	* Calculates a target location to leap. Will consider the max distance and
	* max height to leap.
	*
	* As we consider the max distance and max height to leap, if the mouse
	* world location (desired location to leap) is beyond that, we clamp the
	* value to (try to) get a valid result.
	* 
	* The main method of this function is projecting the current world location
	* under mouse on the navigation system, allowing to find a valid location
	* to leap.
	*
	* However, we may get invalid results if the desired location is too far
	* from a valid navigation system location. In this case, we try to shorten
	* the desired location by getting the max distance we can leap, and using
	* that to find a valid location on navigation system to leap towards. This
	* is useful if the player is hovering the mouse over the abyss. The final
	* location will basically be the furthest we can reach towards that
	* direction.
	*/
	UFUNCTION(BlueprintCallable, Category="GASTargeting")
	static FLeapTargetResult CalculateLeapTarget(UObject* WorldContextObject,
		const APlayerController* PlayerController, const FVector& Origin,
		float MaxDistance, float MaxHeight, bool TraceMaxDistance);
};
