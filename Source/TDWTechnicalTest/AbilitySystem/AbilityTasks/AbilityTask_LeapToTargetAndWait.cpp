// Copyright Saulo Soares. All rights reserved.


#include "AbilityTask_LeapToTargetAndWait.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"


UAbilityTask_LeapToTargetAndWait::UAbilityTask_LeapToTargetAndWait()
{
	bTickingTask = true;
}

UAbilityTask_LeapToTargetAndWait* UAbilityTask_LeapToTargetAndWait::Leap(
	UGameplayAbility* OwningAbility, FVector InTargetLocation,
	UCurveFloat* InHorizontalCurve, UCurveFloat* InHeightCurve)
{
	UAbilityTask_LeapToTargetAndWait* Task =
		NewAbilityTask<UAbilityTask_LeapToTargetAndWait>(OwningAbility);

	Task->TargetLocation = InTargetLocation;
	Task->HorizontalCurve = InHorizontalCurve;
	Task->HeightCurve = InHeightCurve;
	
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
	auto* Character = Cast<ACharacter>(GetAvatarActor());
	if (!Character)
	{
		EndTask();
		return;
	}

	StartLeap();
}

void UAbilityTask_LeapToTargetAndWait::StartLeap()
{
	auto* Character = Cast<ACharacter>(GetAvatarActor());

	LeapStartLocation = Character->GetActorLocation();
	TargetLocation.Z +=
		Character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	ElapsedTime = 0.f;

	Character->GetCharacterMovement()->DisableMovement();
	bIsLeaping = true;
}

void UAbilityTask_LeapToTargetAndWait::UpdateLeap(float DeltaTime)
{
	ElapsedTime += DeltaTime;
	CurrentLeapProgress = FMath::Clamp(ElapsedTime / LeapDuration, 0.f, 1.f);

	const auto HorizontalAlpha = HorizontalCurve->GetFloatValue(
		CurrentLeapProgress);
	const auto HorizontalPosition = UKismetMathLibrary::VLerp(LeapStartLocation,
		TargetLocation, HorizontalAlpha);

	const auto ArcHeight = HeightCurve->GetFloatValue(CurrentLeapProgress) *
		MaxArcHeight;
	const auto CurrentHeight = FVector(0.f, 0.f, ArcHeight);

	const auto FinalPos = HorizontalPosition + CurrentHeight;
	
	auto* Character = Cast<ACharacter>(GetAvatarActor());
	Character->SetActorLocation(FinalPos);

	if (CurrentLeapProgress >= 1.f)
	{
		FinishLeap();
	}
}

void UAbilityTask_LeapToTargetAndWait::FinishLeap()
{
	bIsLeaping = false;

	auto* Character = Cast<ACharacter>(GetAvatarActor());
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
	OnLanded.Broadcast();
	EndTask();
}
