// Copyright Saulo Soares. All rights reserved.

#include "CombatSet.h"

void UCombatSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute,
	float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UCombatSet::PreAttributeChange(const FGameplayAttribute& Attribute,
	float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UCombatSet::ClampAttribute(const FGameplayAttribute& Attribute,
	float& NewValue) const
{
	if (Attribute == GetAttackSpeedAttribute())
	{
		// Do not allow health to go negative
		// "100.f" is a safe value for this clamp. The attack speed will
		// unlikely go that higher
		NewValue = FMath::Clamp(NewValue, 0.0f, 100.0f);
	}
}
