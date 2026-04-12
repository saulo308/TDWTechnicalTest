// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_LeapToTargetAndWait.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeapFinished);

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API UAbilityTask_LeapToTargetAndWait :
	public UAbilityTask
{
	GENERATED_BODY()
	
public:
	/** */
	UAbilityTask_LeapToTargetAndWait();
	
public:
	/** */
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks",
		meta = (DisplayName="LeapToTargetAndWait",
		HidePin = "OwningAbility", DefaultToSelf = "OwningAbility",
		BlueprintInternalUseOnly = "true"))
	static UAbilityTask_LeapToTargetAndWait* Leap(
		UGameplayAbility* OwningAbility, FVector InTargetLocation,
		class UCurveFloat* InHorizontalCurve, class UCurveFloat* InHeightCurve);

public:
	/** Tick function for this task, if bTickingTask == true */
	virtual void TickTask(float DeltaTime) override;
	
	/** */
	virtual void Activate() override;
	
protected:
	/** */
	virtual void StartLeap();

	/** */
	virtual void UpdateLeap(float DeltaTime);

	/** */
	virtual void FinishLeap();
	
public:
	/** */
	UPROPERTY(BlueprintAssignable)
	FLeapFinished OnLanded;
	
protected:
	UPROPERTY()
	TObjectPtr<class UCurveFloat> HorizontalCurve;
	
	UPROPERTY()
	TObjectPtr<class UCurveFloat> HeightCurve;

protected:
	/** */
	FVector TargetLocation = FVector();
	
	/** */
	float MaxArcHeight = 400.f;
	
private:
	/** */
	FVector LeapStartLocation = FVector();

	float ElapsedTime = 0.f;

	bool bIsLeaping = false;

	float CurrentLeapProgress = 0.f;

	float LeapDuration = 1.f;
};
