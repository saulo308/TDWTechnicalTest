// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "MVVMViewModelBase.h"
#include "VM_CharacterVitals.generated.h"

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API UVM_CharacterVitals : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	/** */
	UFUNCTION(BlueprintCallable)
	void InitializeFromASC(class UAbilitySystemComponent* TargetAsc);
 
	/** */
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthPercent() const;
	
	/** */
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetManaPercent() const;
	
public:
	void SetCurrentHealth(float NewCurrentHealth);
 
	void SetMaxHealth(float NewMaxHealth);
	
	void SetCurrentMana(float NewCurrentMana);
 
	void SetMaxMana(float NewMaxMana);

	virtual void BeginDestroy() override;

private:
	/** */
	void BindAttribute(const FGameplayAttribute& Attribute,
		TFunction<void(float)> OnChanged);
	
	/** */
	void UnbindAllAttributes();
	
	/** */
	void UnbindAttribute(const FGameplayAttribute& Attribute);
	
private:
	/** */
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter,
		meta=(AllowPrivateAccess))
	float CurrentHealth = 0.f;
		
	/** */
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter,
		meta=(AllowPrivateAccess))
	float MaxHealth = 0.f;
	
	/** */
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter,
		meta=(AllowPrivateAccess))
	float CurrentMana = 0.f;
		
	/** */
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter,
		meta=(AllowPrivateAccess))
	float MaxMana = 0.f;
	
	/** */
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> OwningAsc;

private:
	/** */
	TMap<FGameplayAttribute, FDelegateHandle> AttributeDelegateHandles;
};
