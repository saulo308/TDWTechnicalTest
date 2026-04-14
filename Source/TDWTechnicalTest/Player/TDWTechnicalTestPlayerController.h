// Copyright Saulo Soares. All rights reserved.

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

public:
	/** */
	UFUNCTION(BlueprintCallable)
	class ATDWTestPlayerState* GetTDWTestPlayerState() const;

	/** */
	UFUNCTION(BlueprintCallable)
	class UTDWTestAbilitySystemComponent* GetTDWTestAbilitySystemComponent()
		const;

public:
	/** */
	virtual void PostProcessInput(const float DeltaTime,
		const bool bGamePaused) override;
	
protected:
	
	virtual void SetupInputComponent() override;

	/** Called when the game starts */
	virtual void BeginPlay();
};


