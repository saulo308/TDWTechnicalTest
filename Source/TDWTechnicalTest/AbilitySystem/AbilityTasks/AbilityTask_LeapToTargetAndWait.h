// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_LeapToTargetAndWait.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeapApexReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeapFinished);


/**
* Ability task that smoothly makes the avatar character to leap in an arc
* towards a target location. The leap is controlled through a [0,1] alpha value,
* letting us fully control the leap trajectory.
*
* The caller can define curves to define the horizontal and vertical movement
* feel, as they define how fast/slow the character will reach its final
* horizontal location and update its height during the leap, allowing a great
* range of different leaps.
* 
* Also, the ability task allows to define the leap's duration and its max arc
* height.
*/
UCLASS()
class TDWTECHNICALTEST_API UAbilityTask_LeapToTargetAndWait :
	public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UAbilityTask_LeapToTargetAndWait();
	
public:
	/**
	* Leaps in an arc towards a target location. The curves define the feel of
	* the leap, as it defines how fast/slow the horizontal and vertical
	* values should be applied to the character.
	*
	* @param InTargetLocation The target location to leap towards.
	* @param InHorizontalCurve The curve that defines how fast/slow horizontal
	* movement is applied.
	* @param InHeightCurve The curve that defines how fast/slow vertical
	* movement is applied.
	* @param InLeapDuration The leap's duration.
	* @param InMaxArcHeight The leap's max arc height.
	*/
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks",
		meta = (DisplayName="LeapToTargetAndWait",
		HidePin = "OwningAbility", DefaultToSelf = "OwningAbility",
		BlueprintInternalUseOnly = "true"))
	static UAbilityTask_LeapToTargetAndWait* Leap(
		UGameplayAbility* OwningAbility, FVector InTargetLocation,
		class UCurveFloat* InHorizontalCurve, class UCurveFloat* InHeightCurve,
		float InLeapDuration = 1.f,	float InMaxArcHeight = 400.f);

public:
	virtual void TickTask(float DeltaTime) override;
	
	virtual void Activate() override;
	
protected:
	/**
	* Calculates the starting location, allowing smoothly location interpolation
	* to target location.
	*/
	virtual void StartLeap();

	/**
	* Called at each frame, allowing smooth location interpolation to the final
	* leap target location by considering the horizontal and vertical curves
	* as the leap progresses.
	*/
	virtual void UpdateLeap(float DeltaTime);

	/** Ends the leap. */
	virtual void FinishLeap();
	
public:
	/** Called when the leap has reached its apex. */
	UPROPERTY(BlueprintAssignable)
	FLeapApexReached OnApexReached;
	
	/** Called when the character has landed on the final target location. */
	UPROPERTY(BlueprintAssignable)
	FLeapFinished OnLanded;
	
protected:
	UPROPERTY()
	TObjectPtr<class UCurveFloat> HorizontalCurve;
	
	UPROPERTY()
	TObjectPtr<class UCurveFloat> HeightCurve;

protected:
	FVector TargetLocation = FVector();
	
	float MaxArcHeight = 0.f;

private:
	UPROPERTY()
	TObjectPtr<ACharacter> Character;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> OwnerASC;
	
private:
	FVector LeapStartLocation = FVector();

	float ElapsedTime = 0.f;

	bool bIsLeaping = false;

	float CurrentLeapProgress = 0.f;

	float LeapDuration = 1.f;

	bool bPassedApex = false;
};
