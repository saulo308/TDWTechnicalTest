// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASTargetingLibrary.generated.h"

/** */
USTRUCT(BlueprintType)
struct FLeapTargetResult
{

	GENERATED_BODY()

public:
	/** */
	UPROPERTY(BlueprintReadOnly)
	FVector Location = FVector();
	
	/** */
	UPROPERTY(BlueprintReadOnly)
	bool bIsValid = false;
};

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
	
	/** */
	UFUNCTION(BlueprintCallable, Category="GASTargeting")
	static FLeapTargetResult CalculateLeapTarget(UObject* WorldContextObject,
		const APlayerController* PlayerController, const FVector& Origin,
		float MaxDistance, float MaxHeight);
};
