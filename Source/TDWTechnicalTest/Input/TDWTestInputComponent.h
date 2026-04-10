// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "Data/TDWTestInputConfig.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"
#include "TDWTestInputComponent.generated.h"

/**
* 
*/
UCLASS()
class TDWTECHNICALTEST_API UTDWTestInputComponent : 
    public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	/** */
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const class UTDWTestInputConfig* InputConfig,
		UserClass* Object, PressedFuncType PressedFunc,
		ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);

	/** */
	template<class UserClass, typename FuncType>
	void BindNativeAction(const class UTDWTestInputConfig* InputConfig,
		const FGameplayTag& InputTag, ETriggerEvent TriggerEvent,
		UserClass* Object, FuncType Func, bool bLogIfNotFound);
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UTDWTestInputComponent::BindAbilityActions(
	const UTDWTestInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc,
	TArray<uint32>& BindHandles)
{
	if (!InputConfig)
	{
		TDWTestLog_ERROR(TEXT("Can't bind ability actions with invalid input "
			"config."));
		return;	
	}

	// Bind each ability input action "triggered" and "completed" events
	for (const auto& Action : InputConfig->AbilityInputActions)
	{
		if (!Action.InputAction || !Action.InputTag.IsValid())
		{
			TDWTestLog_ERROR(TEXT("Invalid input action found on ability "
				"input actions on input config."));
			continue;
		}

		if (PressedFunc)
		{
			const auto Handle = BindAction(Action.InputAction,
				ETriggerEvent::Started, Object, PressedFunc,
				Action.InputTag).GetHandle();
			BindHandles.Add(Handle);
		}

		if (ReleasedFunc)
		{
			const auto Handle = BindAction(Action.InputAction,
				ETriggerEvent::Completed, Object, ReleasedFunc,
				Action.InputTag).GetHandle();
			BindHandles.Add(Handle);
		}
	}
}

template<class UserClass, typename FuncType>
void UTDWTestInputComponent::BindNativeAction(
	const UTDWTestInputConfig* InputConfig, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func,
	bool bLogIfNotFound)
{
	if (!InputConfig)
	{
		TDWTestLog_ERROR(TEXT("Can't bind native action with invalid "
			"input config. Input tag: [%s]."), *InputTag.ToString());
		return;	
	}
	
	if (!Object)
	{
		TDWTestLog_ERROR(TEXT("Can't bind native action to invalid "
			"object. Input tag: [%s]."), *InputTag.ToString());
		return;
	}
	
	// Find the input action by its tag on the input config
	check(InputConfig);
	const auto TargetInputAction = InputConfig->FindNativeInputActionByTag(
		InputTag, bLogIfNotFound);

	// If found, bind it to the object's function
	if (TargetInputAction)
	{
		BindAction(TargetInputAction, TriggerEvent, Object, Func);
	}
}
