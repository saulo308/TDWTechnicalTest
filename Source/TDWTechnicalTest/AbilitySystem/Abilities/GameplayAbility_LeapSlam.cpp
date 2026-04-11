// Copyright Saulo Soares. All rights reserved.


#include "GameplayAbility_LeapSlam.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTechnicalTest/AbilitySystem/BlueprintLibraries/GASTargetingLibrary.h"

void UGameplayAbility_LeapSlam::StartTargeting(bool bDebugTraces)
{
	// 1. Get actors in range
	TArray<AActor*> Targets;

	const FVector ImpactLocation =
		GetAvatarActorFromActorInfo()->GetActorLocation();
	
	TArray<TEnumAsByte<ECollisionChannel>> Channels;
	Channels.Add(ECC_Pawn);
	UGASTargetingLibrary::GetActorsInRadius(GetWorld(), ImpactLocation,
		500.f, Channels, Targets, GetAvatarActorFromActorInfo());

	TDWTestLog_ERROR(TEXT("Actors found: %d"), Targets.Num());
	for (const auto& Target : Targets)
	{
		TDWTestLog_ERROR(TEXT("\t%s"), *Target->GetName());
	}

	// 2. Build target data
	const auto TargetData = BuildTargetDataFromActors(Targets);

	// 3. Call
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
