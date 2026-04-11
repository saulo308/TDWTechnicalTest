// Copyright Saulo Soares. All rights reserved.


#include "GASTargetingLibrary.h"
#include "Engine/OverlapResult.h"
#include "Engine/World.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"

void UGASTargetingLibrary::GetActorsInRadius(UWorld* World,
	const FVector& Origin, float Radius,
	const TArray<TEnumAsByte<ECollisionChannel>>& ObjectTypes,
	TArray<AActor*>& OutActors, AActor* IgnoreActor)
{
	if (!World)
	{
		return;
	}

	TArray<FOverlapResult> Overlaps;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(IgnoreActor);
	
	FCollisionObjectQueryParams ObjectQuery;
	for (ECollisionChannel Channel : ObjectTypes)
	{
		ObjectQuery.AddObjectTypesToQuery(Channel);
	}
	
	World->OverlapMultiByObjectType(Overlaps, Origin, FQuat::Identity,
		ObjectQuery, Sphere,Params);
	
	DrawDebugSphere(World, Origin, Radius, 32, FColor::Green, false, 2.0f);

	for (const auto& Result : Overlaps)
	{
		if (auto* Actor = Result.GetActor())
		{
			OutActors.AddUnique(Actor);
		}
	}
}
