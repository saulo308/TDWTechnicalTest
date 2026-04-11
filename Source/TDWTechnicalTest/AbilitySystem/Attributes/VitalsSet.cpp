// Copyright Saulo Soares. All rights reserved.

#include "VitalsSet.h"
#include "GameplayEffectExtension.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"

void UVitalsSet::PostGameplayEffectExecute(
	const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Convert into "-Health" and then clamp
		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), 0.f, GetMaxHealth()));
		SetDamage(0.0f);
	}
}

void UVitalsSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute,
	float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UVitalsSet::PreAttributeChange(const FGameplayAttribute& Attribute,
	float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UVitalsSet::ClampAttribute(const FGameplayAttribute& Attribute,
	float& NewValue) const
{
	if (Attribute == GetHealthAttribute())
	{
		// Do not allow health to go negative or above max health.
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
		return;
	}
	
	if (Attribute == GetMaxHealthAttribute())
	{
		// Do not allow max health to drop below 1.
		NewValue = FMath::Max(NewValue, 1.0f);
		return;
	}
	
	if (Attribute == GetManaAttribute())
	{
		// Do not allow mana to go negative or above max mana.
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
		return;
	}
	
	if (Attribute == GetMaxManaAttribute())
	{
		// Do not allow max mana to drop below 1.
		NewValue = FMath::Max(NewValue, 1.0f);
	}
}
