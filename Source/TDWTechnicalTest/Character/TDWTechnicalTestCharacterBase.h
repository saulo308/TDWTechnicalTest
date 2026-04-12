// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDWTechnicalTestCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilitySystemComponentInitialized);

UCLASS(Blueprintable)
class ATDWTechnicalTestCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	/** Default constructor */
	ATDWTechnicalTestCharacterBase();

	/** Called every frame. */
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	/** */
	virtual void SetupPlayerInputComponent(
		UInputComponent* PlayerInputComponent) override;

protected:
	/** */
	UPROPERTY(BlueprintAssignable)
	FOnAbilitySystemComponentInitialized OnAbilitySystemComponentInitialized;
};
