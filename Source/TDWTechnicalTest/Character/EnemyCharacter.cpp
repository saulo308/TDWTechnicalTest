// Copyright Saulo Soares. All rights reserved.


#include "EnemyCharacter.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTechnicalTest/AbilitySystem/AbilitySet.h"
#include "TDWTechnicalTest/AbilitySystem/TDWTestAbilitySystemComponent.h"
#include "TDWTechnicalTest/Character/Data/PawnData.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<
		UTDWTestAbilitySystemComponent>(TEXT("AbilitySystem"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitAbilitySystemComponent();

	if (const auto LoadedPawnData = DefaultPawnData.LoadSynchronous())
	{
		SetPawnData(LoadedPawnData);
	}

	OnAbilitySystemComponentInitialized.Broadcast();
}

void AEnemyCharacter::InitAbilitySystemComponent()
{
	// Init the ability actor info
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	TDWTestLog_INFO(TEXT("Initialized character [%s] ASC."), *GetName());
}

void AEnemyCharacter::SetPawnData(const TObjectPtr<UPawnData>& PawnData)
{
	if (!PawnData)
	{
		TDWTestLog_WARNING(TEXT("No pawn data was passed to enemy character."));
		return;
	}

	CurrentPawnData = PawnData;

	// Foreach ability set from pawn data, give it to the player's ASC
	for (const auto AbilitySet : PawnData->AbilitySets)
	{
		if (!AbilitySet)
		{
			continue;
		}
		
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
	}
}

UAbilitySystemComponent* AEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
