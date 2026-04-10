// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/CharacterInputHandler.h"
#include "GameFramework/Character.h"
#include "TDWTechnicalTestCharacter.generated.h"

UCLASS(Blueprintable)
class ATDWTechnicalTestCharacter : public ACharacter,
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
	* Called once the Character is possessed on the server. Will initialize
	* the ASC on the server.
	*/
	virtual void PossessedBy(AController* NewController) override;
	
	/** */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	/** */
	virtual void SetupPlayerInputComponent(
		UInputComponent* PlayerInputComponent) override;

private:
	/**
	* Initializes the ASC. Will call "InitAbilityActorInfo" on it, passing the
	* PlayerState as owner and the Character as the avatar.
	*/
	void InitAbilitySystemComponent();

protected:
	/** */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UTDWTestAbilitySystemComponent> AbilitySystemComponent;
	
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent = nullptr;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom = nullptr;

	/** */
	UPROPERTY()
	TObjectPtr<class UCharacterInputHandler> InputHandler;
};
