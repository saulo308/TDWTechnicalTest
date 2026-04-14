// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "TDWTechnicalTest/Input/Data/TDWTestInputConfig.h"
#include "TDWTechnicalTest/Character/Data/PawnData.h"
#include "CharacterInputHandler.generated.h"

/** Handles player input bindings. */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDWTECHNICALTEST_API UCharacterInputHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	/** Sets default values for this component's properties */
	UCharacterInputHandler();

	/**
	* Initializes player's native and ability input actions by binding
	* them to callbacks.
	*
	* Also, initializes the desired IMCs from pawn data.
	*/
	virtual void InitializePlayerInput(
		const TObjectPtr<class UInputComponent>& InputComponent,
		const TObjectPtr<class UPawnData>& PawnData);

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

private:
	/** Movement input. */
	UFUNCTION()
	void Input_Move(const FInputActionValue& InputActionValue);
	
	/**
	* Called when an input action has been pressed. The callback receives the
	* input tag defined to be bound to the input action. This will be sent to
	* the player's ASC, which will keep track of which input tag is being
	* pressed at this frame.
	*
	* During input processing in the ASC, it will either activate or send
	* "input pressed" event to the matching input tag ability.
	*/
	UFUNCTION()
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);

	/**
	* Called when an input action has been released. The callback receives the
	* input tag defined to be bound to the input action. This will be sent to
	* the player's ASC, which will keep track of which input tag is being
	* released at this frame.
	*
	* During input processing in the ASC, it will send "input released" event to
	* the matching input tag ability.
	*/
	UFUNCTION()
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);
	
private:
	bool RegisterDefaultInputMappingContexts(
		TArray<FInputMappingContextData>& InputMappings);
	
	void RegisterNativeActions(
		const TObjectPtr<UInputComponent>& InputComponent,
		const TObjectPtr<class UTDWTestInputConfig>& InputConfig);
	
	void RegisterAbilityActions(
		const TObjectPtr<UInputComponent>& InputComponent,
		const TObjectPtr<class UTDWTestInputConfig>& InputConfig);

private:
	UPROPERTY()
	TObjectPtr<APawn> OwnerPawn;

	UPROPERTY()
	TObjectPtr<APlayerController> OwnerPlayerController;
};
