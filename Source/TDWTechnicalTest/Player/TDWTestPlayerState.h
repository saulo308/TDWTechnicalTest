// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "TDWTestPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TDWTECHNICALTEST_API ATDWTestPlayerState : public APlayerState,
	public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	/** */
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** */
	UFUNCTION(BlueprintCallable)
	class UTDWTestAbilitySystemComponent* GetTDWTestAbilitySystemComponent()
		const { return AbilitySystemComponent; }
	
public:
	/** Sets default values for this character's properties */
	ATDWTestPlayerState();

	/** */
	void SetPawnData(const TObjectPtr<class UPawnData>& PawnData);

private:
	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UTDWTestAbilitySystemComponent> AbilitySystemComponent;

	/** */
	UPROPERTY()
	TObjectPtr<class UPawnData> CurrentPawnData;
};
