// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASTargetingLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API UGASTargetingLibrary :
	public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** */
	UFUNCTION(BlueprintCallable, Category="GASTargeting")
	static void GetActorsInRadius(UWorld* World, const FVector& Origin,
		float Radius, const TArray<TEnumAsByte<ECollisionChannel>>& ObjectTypes,
		TArray<AActor*>& OutActors, AActor* IgnoreActor = nullptr);
};
