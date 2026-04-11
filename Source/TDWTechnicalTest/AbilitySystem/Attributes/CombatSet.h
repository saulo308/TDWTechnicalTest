// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"
#include "CombatSet.generated.h"

/**
*  
*/
UCLASS(BlueprintType)
class TDWTECHNICALTEST_API UCombatSet : public UAttributeSetBase
{
	GENERATED_BODY()

public:
	/** */
	ATTRIBUTE_ACCESSORS(UCombatSet, AttackSpeed);

private:
	/** */
	UPROPERTY(BlueprintReadOnly, Category = "TDWTest|Combat",
		Meta=(AllowPrivateAccess = true))
	FGameplayAttributeData AttackSpeed;
};
