// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"
#include "CombatSet.generated.h"

/** Attribute set for base damange and attack speed. */
UCLASS(BlueprintType)
class TDWTECHNICALTEST_API UCombatSet : public UAttributeSetBase
{
	GENERATED_BODY()

protected:
	/** Clamps attribute values to avoid any invalid state. */
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute,
		float& NewValue) const override;
	
	/** Clamps attribute values to avoid any invalid state. */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute,
		float& NewValue) override;

private:
	/**
	* Clamps the given attribute to avoid its invalid state. E.g., attack
	* speed < 0.
	*
	* @param Attribute The attribute to clamp.
	* @param NewValue The attribute's new desired value.
	*/
	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue)
		const;
	
public:
	ATTRIBUTE_ACCESSORS(UCombatSet, AttackSpeed);
	ATTRIBUTE_ACCESSORS(UCombatSet, BaseDamage);

private:
	UPROPERTY(BlueprintReadOnly, Category = "TDWTest|Combat",
		Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData AttackSpeed;
	
	UPROPERTY(BlueprintReadOnly, Category = "TDWTest|Combat",
		Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData BaseDamage;
};
