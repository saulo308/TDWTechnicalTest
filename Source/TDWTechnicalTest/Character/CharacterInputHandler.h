// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "TDWTechnicalTest/Input/Data/TDWTestInputConfig.h"
#include "CharacterInputHandler.generated.h"

/**
* 
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDWTECHNICALTEST_API UCharacterInputHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	/** Sets default values for this component's properties */
	UCharacterInputHandler();

	/** */
	virtual void InitializePlayerInput(
		TObjectPtr<class UInputComponent> InputComponent);

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

private:
	/** */
	UFUNCTION()
	void Input_Move(const FInputActionValue& InputActionValue);
	
private:
	/** */
	bool RegisterDefaultInputMappingContexts();
	
	/** */
	void RegisterNativeActions(
		const TObjectPtr<UInputComponent>& InputComponent);
	
protected:
	/** */
	UPROPERTY(EditAnywhere)
	TArray<FInputMappingContextData> CharacterDefaultInputMappings;

	/** */
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTDWTestInputConfig> CharacterInputConfig;
	
private:
	/** */
	UPROPERTY()
	TObjectPtr<APawn> OwnerPawn;

	/** */
	UPROPERTY()
	TObjectPtr<APlayerController> OwnerPlayerController;
};
