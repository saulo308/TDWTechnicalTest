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
};
