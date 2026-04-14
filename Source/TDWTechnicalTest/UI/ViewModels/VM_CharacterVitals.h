// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "MVVMViewModelBase.h"
#include "VM_CharacterVitals.generated.h"

/**
* The UI uses MVVM architecture. By defining a view model, we can decouple the
* UMG widgets from gameplay logic. With this design, the gameplay logic will
* only update the view model. On the other hand, the MVVM plugin allows us to
* define view model bindings on UMG widgets and load their reference. Thus, this
* allows designer to build any widget they want, and use the data from the view
* model the way they please, while gameplay logic is only concerned of updating
* the view model, regardless of how the UI looks.
*
* Also, another benefit is that view models use automatic event-driven logic,
* as UMG widgets bind to FieldNotify functions/properties. From that, the view
* model only broadcasts when the change macros are called (e.g.,
* "UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED"). Thus, UI doesn't need to keep
* polling data every frame.
*
* One downside is that view models cache the data coming from gameplay logic.
* Which may somewhat be acceptable, as it works as a "centralized data hub" for
* UI.
*
* Here we define the character vitals view model. It contains the health and
* mana data that are updated from an ASC. Once these attributes change on ASC,
* the view model gets updated. If any UMG is bound to a modified
* function/property, its bind will get automatically called; updating the UI.
*/
UCLASS()
class TDWTECHNICALTEST_API UVM_CharacterVitals : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	/**
	* Initialization from an ASC. Allows us to define the cached data in
	* this view model.
	*
	* @param TargetAsc The target ASC that will update the view model data.
	*/
	UFUNCTION(BlueprintCallable)
	void InitializeFromASC(class UAbilitySystemComponent* TargetAsc);
 
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthPercent() const;
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetManaPercent() const;
	
public:
	void SetCurrentHealth(float NewCurrentHealth);
	void SetMaxHealth(float NewMaxHealth);
	void SetCurrentMana(float NewCurrentMana);
	void SetMaxMana(float NewMaxMana);

	/** Unbinds from ASC to avoid "dangling" references to delegates. */
	virtual void BeginDestroy() override;

private:
	/**
	* Binds an attribute changed delegate to a callback. The callback will
	* update the view model cached data.
	*
	* @param Attribute The attribute to get its changed delegate to bind to a
	* callback.
	* @param OnChanged The callback to call when the attribute has its value
	* modified.
	*/
	void BindAttribute(const FGameplayAttribute& Attribute,
		TFunction<void(float)> OnChanged);
	
	void UnbindAllAttributes();
	void UnbindAttribute(const FGameplayAttribute& Attribute);
	
private:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter,
		meta=(AllowPrivateAccess))
	float CurrentHealth = 0.f;
		
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter,
		meta=(AllowPrivateAccess))
	float MaxHealth = 0.f;
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter,
		meta=(AllowPrivateAccess))
	float CurrentMana = 0.f;
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter,
		meta=(AllowPrivateAccess))
	float MaxMana = 0.f;

	/** The ASC that has its attributes bound to this view model data. */
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> OwningAsc;

private:
	/** Cache the attribute changed delegates to allow unbinding later. */
	TMap<FGameplayAttribute, FDelegateHandle> AttributeDelegateHandles;
};
