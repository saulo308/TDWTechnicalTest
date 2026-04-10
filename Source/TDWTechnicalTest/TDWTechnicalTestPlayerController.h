// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "TDWTechnicalTestPlayerController.generated.h"

UCLASS()
class ATDWTechnicalTestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Default constructor */
	ATDWTechnicalTestPlayerController();

protected:
	
	virtual void SetupInputComponent() override;

	/** Called when the game starts */
	virtual void BeginPlay();
};


