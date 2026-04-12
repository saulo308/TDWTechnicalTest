// Copyright Saulo Soares. All rights reserved.


#include "GameplayAbility_LeapSlam.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTechnicalTest/AbilitySystem/BlueprintLibraries/GASTargetingLibrary.h"

void UGameplayAbility_LeapSlam::StartTargeting(float AoERadius,
	bool bDebugTrace)
{
	const FVector TargetingLocation =
		GetAvatarActorFromActorInfo()->GetActorLocation();

	// Get all actors in range of ability 
	TArray<AActor*> Targets;
	TArray<TEnumAsByte<ECollisionChannel>> Channels;
	Channels.Add(ECC_Pawn);
	UGASTargetingLibrary::GetActorsInRadius(GetWorld(), TargetingLocation,
		AoERadius, Channels, bDebugTrace, Targets, GetAvatarActorFromActorInfo());

	// Build target data from found actors (if any)
	const auto TargetData = BuildTargetDataFromActors(Targets);

	// Broadcast that the target data is ready and can be processed in BP
	OnTargetDataReady(TargetData);
}

FGameplayAbilityTargetDataHandle
	UGameplayAbility_LeapSlam::BuildTargetDataFromActors(
	const TArray<AActor*>& Actors)
{
	FGameplayAbilityTargetDataHandle Handle;

	FGameplayAbilityTargetData_ActorArray* Data =
		new FGameplayAbilityTargetData_ActorArray();
	Data->TargetActorArray.Append(Actors);

	Handle.Add(Data);
	return Handle;
}
