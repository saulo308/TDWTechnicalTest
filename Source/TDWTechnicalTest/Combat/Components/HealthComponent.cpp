// Copyright Saulo Soares. All rights reserved.


#include "HealthComponent.h"
#include "AbilitySystemComponent.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTechnicalTest/AbilitySystem/Attributes/VitalsSet.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::InitializeWithAbilitySystem(
	UAbilitySystemComponent* InASC)
{
	if (!InASC)
	{
		TDWTestLog_ERROR(TEXT("Can't initialize [%s] health component with "
			"invalid ASC."), *GetOwner()->GetName());
		return;
	}
	
	VitalsSet = InASC->GetSet<UVitalsSet>();
	if(VitalsSet)
	{
		VitalsSet->OnOutOfHealth.AddUObject(this,
			&UHealthComponent::HandleOutOfHealth);
	}
}

void UHealthComponent::HandleOutOfHealth()
{
	if (VitalsSet)
	{
		VitalsSet->OnOutOfHealth.RemoveAll(this);
	}

	VitalsSet = nullptr;

	// Simple death handling. This should be much more complex.
	GetOwner()->Destroy();
}
