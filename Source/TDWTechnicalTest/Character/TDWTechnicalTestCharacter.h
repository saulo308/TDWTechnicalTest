// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "CharacterInputHandler.h"
#include "TDWTechnicalTestCharacterBase.h"
#include "TDWTechnicalTestCharacter.generated.h"

/** The base class for player character. Initializes the ASC from player state. */
UCLASS(Blueprintable)
class ATDWTechnicalTestCharacter : public ATDWTechnicalTestCharacterBase,
	public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	/** Default constructor */
	ATDWTechnicalTestCharacter();

	/** Called every frame. */
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const
		{ return TopDownCameraComponent; }
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const
		{ return CameraBoom; }

	/**
	* Called once the Character is possessed. Will initialize the character's
	* ASC.
	*/
	virtual void PossessedBy(AController* NewController) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void SetupPlayerInputComponent(
		UInputComponent* PlayerInputComponent) override;

private:
	/**
	* Initializes the ASC. Will call "InitAbilityActorInfo" on it, passing the
	* PlayerState as owner and the Character as the avatar.
	*/
	void InitAbilitySystemComponent();

protected:
	/** The ASC created on player state. */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UTDWTestAbilitySystemComponent> AbilitySystemComponent;
	
	/**
	* The pawn data contains information on abilities, attributes and gameplay
	* effects to apply to the pawn; as well as input config. Can be seen as
	* "initial abilities, attributes and GEs" to give to player. Will be given
	* after ASC initialization.
	*
	* The pawn data will also be used to initialize player input.
	* 
	* @note SoftObjectPtr as it may reference many assets.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		Category="TDWTestCharacter|PawnData")
	TSoftObjectPtr<class UPawnData> DefaultPawnData;
	
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent = nullptr;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom = nullptr;

	/** Implements player input callbacks. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCharacterInputHandler> InputHandler;
};
