// Copyright Saulo Soares. All rights reserved.


#include "AbilityTask_LeapToTargetAndWait.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TDWTechnicalTest/TDWTestTags.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"

UAbilityTask_LeapToTargetAndWait::UAbilityTask_LeapToTargetAndWait()
{
	bTickingTask = true;
}

UAbilityTask_LeapToTargetAndWait* UAbilityTask_LeapToTargetAndWait::Leap(
	UGameplayAbility* OwningAbility, FVector InTargetLocation,
	UCurveFloat* InHorizontalCurve, UCurveFloat* InHeightCurve,
	float InLeapDuration /*=1.f*/, float InMaxArcHeight /*=400.f*/)
{
	UAbilityTask_LeapToTargetAndWait* Task =
		NewAbilityTask<UAbilityTask_LeapToTargetAndWait>(OwningAbility);

	Task->TargetLocation = InTargetLocation;
	Task->HorizontalCurve = InHorizontalCurve;
	Task->HeightCurve = InHeightCurve;
	Task->LeapDuration = InLeapDuration;
	Task->MaxArcHeight = InMaxArcHeight;
	
	return Task;
}

void UAbilityTask_LeapToTargetAndWait::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (bIsLeaping)
	{
		UpdateLeap(DeltaTime);
	}
}

void UAbilityTask_LeapToTargetAndWait::Activate()
{
	// Get references for leap
	Character = Cast<ACharacter>(GetAvatarActor());
	if (!Character)
	{
		EndTask();
		return;
	}
	
	OwnerASC = AbilitySystemComponent.Get();
	if (!OwnerASC)
	{
		EndTask();
		return;
	}

	// Start leaping
	StartLeap();
}

void UAbilityTask_LeapToTargetAndWait::StartLeap()
{
	check(Character);

	// Get the start leap location, so we can smoothly interpolate
	LeapStartLocation = Character->GetActorLocation();

	// Compensate character capsule half height on the target location, which
	// was generated on a navigable point (on ground);
	TargetLocation.Z +=
		Character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();

	// Add leap state to ASC. Animation system can use this tag to update
	// animations
	check(OwnerASC);
	OwnerASC->AddLooseGameplayTag(TDWTestGameplayTags::LeapMovementState);

	// Avoid player movement during leap
	Character->GetCharacterMovement()->DisableMovement();
	
	ElapsedTime = 0.f;
	bIsLeaping = true;
}

void UAbilityTask_LeapToTargetAndWait::UpdateLeap(float DeltaTime)
{
	// Calculate the current leap progress
	ElapsedTime += DeltaTime;
	CurrentLeapProgress = FMath::Clamp(ElapsedTime / LeapDuration, 0.f, 1.f);

	// Calculate the horizontal offset from start location to apply during this
	// frame
	const auto HorizontalAlpha = HorizontalCurve->GetFloatValue(
		CurrentLeapProgress);
	const auto HorizontalPosition = UKismetMathLibrary::VLerp(LeapStartLocation,
		TargetLocation, HorizontalAlpha);

	// Calculate the vertical offset from start location to apply during this
	// frame
	const auto ArcHeight = HeightCurve->GetFloatValue(CurrentLeapProgress) *
		MaxArcHeight;
	const auto CurrentHeight = FVector(0.f, 0.f, ArcHeight);

	// Set the final position to apply during this frame
	const auto FinalPos = HorizontalPosition + CurrentHeight;
	Character->SetActorLocation(FinalPos);

	// Check for apex
	if (!bPassedApex && CurrentLeapProgress >= 0.5f)
	{
		// Reached apex
		bPassedApex = true;
		OnApexReached.Broadcast();
	}

	// Check for leap finished
	if (CurrentLeapProgress >= 1.f)
	{
		FinishLeap();
	}
}

void UAbilityTask_LeapToTargetAndWait::FinishLeap()
{
	bIsLeaping = false;

	// Reset movement
	check(Character);
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	// Remove state flag
	check(OwnerASC);
	OwnerASC->RemoveLooseGameplayTag(TDWTestGameplayTags::LeapMovementState);
	
	OnLanded.Broadcast();
	EndTask();
}
