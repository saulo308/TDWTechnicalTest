// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
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
	void RegisterDefaultInputMappingContexts();
	
protected:
	/** */
	UPROPERTY(EditAnywhere)
	TArray<FInputMappingContextData> CharacterDefaultInputMappings;

private:
	/** */
	UPROPERTY()
	TObjectPtr<APawn> OwnerPawn;

	/** */
	UPROPERTY()
	TObjectPtr<APlayerController> OwnerPlayerController;
};
