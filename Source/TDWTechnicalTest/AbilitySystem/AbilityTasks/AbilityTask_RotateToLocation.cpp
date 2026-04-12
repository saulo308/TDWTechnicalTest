// Copyright Saulo Soares. All rights reserved.


#include "AbilityTask_RotateToLocation.h"
#include "GameFramework/Character.h"

UAbilityTask_RotateToLocation::UAbilityTask_RotateToLocation()
{
	bTickingTask = true;
}

UAbilityTask_RotateToLocation*
	UAbilityTask_RotateToLocation::RotateCharacterToLocation(
	UGameplayAbility* OwningAbility, FVector InTargetLocation,
	float InSmoothTime/*=5.f*/)
{
	UAbilityTask_RotateToLocation* Task = NewAbilityTask<
		UAbilityTask_RotateToLocation>(OwningAbility);
	
	Task->TargetLocation = InTargetLocation;
	Task->SmoothTime = InSmoothTime;

	return Task;
}

void UAbilityTask_RotateToLocation::Activate()
{
	Super::Activate();

	AActor* Avatar = GetAvatarActor();
	if (!Avatar)
	{
		EndTask();
		return;
	}

	Character = Cast<ACharacter>(Avatar);
	if (!Character.IsValid())
	{
		EndTask();
	}

	bCanRotate = true;
}

void UAbilityTask_RotateToLocation::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (!bCanRotate)
	{
		return;
	}

	if (!Character.IsValid())
	{
		EndTask();
		return;
	}

	const FVector ActorLocation = Character->GetActorLocation();
	FVector Direction = TargetLocation - ActorLocation;
	Direction.Z = 0;

	if (Direction.IsNearlyZero())
	{
		EndTask();
		return;
	}

	const FRotator TargetRotation = Direction.Rotation();
	const FRotator CurrentRotation = Character->GetActorRotation();

	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation,
		TargetRotation,	DeltaTime, SmoothTime);

	Character->SetActorRotation(NewRotation);
	if (CurrentRotation.Equals(TargetRotation, 1.0f))
	{
		bCanRotate = false;
		OnFinished.Broadcast();
		EndTask();
	}
}
