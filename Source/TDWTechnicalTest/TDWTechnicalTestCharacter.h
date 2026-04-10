// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterInputHandler.h"
#include "GameFramework/Character.h"
#include "TDWTechnicalTestCharacter.generated.h"

UCLASS(Blueprintable)
class ATDWTechnicalTestCharacter : public ACharacter
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

protected:
	/** */
	virtual void SetupPlayerInputComponent(
		UInputComponent* PlayerInputComponent) override;

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

inline void ATDWTechnicalTestCharacter::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Initialize the input handler with the player input component
	check(InputHandler);
	InputHandler->InitializePlayerInput(PlayerInputComponent);
}
