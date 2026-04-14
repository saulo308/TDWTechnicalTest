// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "TDWTechnicalTestPlayerController.generated.h"

/**
* Default project player controller.
* 
* We override the player controller to allow input processing of gameplay
* abilities bound to input actions. We do this using a "mapping" of input tags
* (FGameplayTags) to input actions. The input tags are bound to GAs, as well
* as bound to input actions. Once an input action is called, we know that an
* ability should be activated/have its input pressed.
*/
UCLASS()
class ATDWTechnicalTestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Default constructor */
	ATDWTechnicalTestPlayerController();

public:
	UFUNCTION(BlueprintCallable)
	class ATDWTestPlayerState* GetTDWTestPlayerState() const;

	UFUNCTION(BlueprintCallable)
	class UTDWTestAbilitySystemComponent* GetTDWTestAbilitySystemComponent()
		const;

public:
	/**
	* Called every frame to process player input. As an integration with GAS,
	* will process any input sent to the current pawn ASC. The flow is the
	* following:
	*	1. We register GAs with designer-defined gameplay tags (called InputTags).
	*	2. We map input actions to input actions. Once pressed, those tags are
	*	sent to the custom ASC.
	*	3. The custom ASC caches the current pressed/hold/released input tags
	*	during this frame.
	*	4. During player controller input processing, custom ASC will check
	*	which input tags are pressed/hold or were released during this frame,
	*	calling internal functions for the GAs
	*	(try activate/input pressed/input released).
	*/
	virtual void PostProcessInput(const float DeltaTime,
		const bool bGamePaused) override;
	
protected:
	virtual void SetupInputComponent() override;

	/** Called when the game starts */
	virtual void BeginPlay();
};


