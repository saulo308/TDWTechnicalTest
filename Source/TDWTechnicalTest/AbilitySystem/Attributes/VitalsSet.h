// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"
#include "VitalsSet.generated.h"

/**
*
*/
UCLASS(BlueprintType)
class TDWTECHNICALTEST_API UVitalsSet : public UAttributeSetBase
{
	GENERATED_BODY()

protected:
	/** */
	virtual void PostGameplayEffectExecute(
		const FGameplayEffectModCallbackData& Data) override;

	/** */
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute,
		float& NewValue) const override;
	
	/** */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute,
		float& NewValue) override;

private:
	/** */
	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue)
		const;
	
public:
	/** */
	ATTRIBUTE_ACCESSORS(UVitalsSet, Health);
	ATTRIBUTE_ACCESSORS(UVitalsSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UVitalsSet, Mana);
	ATTRIBUTE_ACCESSORS(UVitalsSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UVitalsSet, Damage);
	
	// Delegate to broadcast when the health attribute reaches zero
	mutable FAttributeEvent OnOutOfHealth;
	
private:
	/** */
	UPROPERTY(BlueprintReadOnly, Category = "TDWTest|Vitals",
		Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	/** */
	UPROPERTY(BlueprintReadOnly, Category = "TDWTest|Vitals",
		Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	
	/** */
	UPROPERTY(BlueprintReadOnly, Category = "TDWTest|Vitals",
		Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData Mana;

	
	/** */
	UPROPERTY(BlueprintReadOnly, Category = "TDWTest|Vitals",
		Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData MaxMana;
	
	// -------------------------------------------------------------------
	//	Meta Attributes
	// -------------------------------------------------------------------

	// Incoming damage. This is mapped directly to -Health
	UPROPERTY(BlueprintReadOnly, Category="TDWTest|Vitals",
		Meta=(HideFromModifiers, AllowPrivateAccess=true))
	FGameplayAttributeData Damage;
	
private:
	// Used to track when the health reaches 0.
	bool bOutOfHealth = false;
};
