// Copyright Saulo Soares. All rights reserved.


#include "VM_CharacterVitals.h"
#include "AbilitySystemComponent.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTechnicalTest/AbilitySystem/Attributes/VitalsSet.h"

void UVM_CharacterVitals::InitializeFromASC(UAbilitySystemComponent* TargetAsc)
{
	if(!TargetAsc)
	{
		TDWTestLog_ERROR(TEXT("Can't initialize CharacterVitals view model "
			"with invalid ASC."));
		return;
	}

	// Bind attributes modification to update UI
	OwningAsc = TargetAsc;
	BindAttribute(UVitalsSet::GetHealthAttribute(),
		[this](float Value){ SetCurrentHealth(Value); });

	BindAttribute(UVitalsSet::GetMaxHealthAttribute(),
		[this](float Value){ SetMaxHealth(Value); });

	BindAttribute(UVitalsSet::GetManaAttribute(),
		[this](float Value){ SetCurrentMana(Value); });

	BindAttribute(UVitalsSet::GetMaxManaAttribute(),
		[this](float Value){ SetMaxMana(Value); });

	// Initialize initial values
	SetCurrentHealth(OwningAsc->GetNumericAttribute(UVitalsSet::GetHealthAttribute()));
	SetMaxHealth(OwningAsc->GetNumericAttribute(UVitalsSet::GetMaxHealthAttribute()));
	SetCurrentMana(OwningAsc->GetNumericAttribute(UVitalsSet::GetManaAttribute()));
	SetMaxMana(OwningAsc->GetNumericAttribute(UVitalsSet::GetMaxManaAttribute()));
}

void UVM_CharacterVitals::BeginDestroy()
{
	UnbindAllAttributes();
	Super::BeginDestroy();
}

void UVM_CharacterVitals::BindAttribute(const FGameplayAttribute& Attribute,
	TFunction<void(float)> OnChanged)
{
	if (!OwningAsc)
	{
		return;
	}

	// Prevent double binding
	if (AttributeDelegateHandles.Contains(Attribute))
	{
		return;
	}

	FDelegateHandle Handle = OwningAsc->GetGameplayAttributeValueChangeDelegate(
		Attribute).AddWeakLambda(this,
		[this, OnChanged](const FOnAttributeChangeData& Data)
		{
			OnChanged(Data.NewValue);
		});

	AttributeDelegateHandles.Add(Attribute, Handle);
}

void UVM_CharacterVitals::UnbindAllAttributes()
{
	if (!OwningAsc)
	{
		return;
	}

	for (const auto& Pair : AttributeDelegateHandles)
	{
		OwningAsc->GetGameplayAttributeValueChangeDelegate(Pair.Key).Remove(
			Pair.Value);
	}

	AttributeDelegateHandles.Empty();
}

void UVM_CharacterVitals::UnbindAttribute(const FGameplayAttribute& Attribute)
{
	if (!OwningAsc)
	{
		return;
	}

	if (const auto* Handle = AttributeDelegateHandles.Find(Attribute))
	{
		OwningAsc->GetGameplayAttributeValueChangeDelegate(Attribute).Remove(
			*Handle);
		AttributeDelegateHandles.Remove(Attribute);
	}
}

void UVM_CharacterVitals::SetCurrentHealth(float NewCurrentHealth)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentHealth, NewCurrentHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}
 
void UVM_CharacterVitals::SetMaxHealth(float NewMaxHealth)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, NewMaxHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

void UVM_CharacterVitals::SetCurrentMana(float NewCurrentMana)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentMana, NewCurrentMana))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaPercent);
	}
}
 
void UVM_CharacterVitals::SetMaxMana(float NewMaxMana)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxMana, NewMaxMana))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaPercent);
	}
}

float UVM_CharacterVitals::GetHealthPercent() const
{
	if (!FMath::IsNearlyZero(MaxHealth))
	{
		return CurrentHealth / MaxHealth;
	}

	return 0.f;
}

float UVM_CharacterVitals::GetManaPercent() const
{
	if (!FMath::IsNearlyZero(MaxMana))
	{
		return CurrentMana / MaxMana;
	}

	return 0.f;
}
