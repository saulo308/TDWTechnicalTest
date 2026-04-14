// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "TDWTestPlayerState.generated.h"

/**
* The project's player state. Following best practices of GAS usage, the
* ASC for player lives in the player state. This may be better than creating
* the ASC on character, as player state is more "persistent". I.e., while
* characters can be possessed/unpossessed, the player state will remain the same
* throughout the gameplay. This allows us to keep information even if the
* current character gets changed (e.g., if dead).
*/
UCLASS()
class TDWTECHNICALTEST_API ATDWTestPlayerState : public APlayerState,
	public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	class UTDWTestAbilitySystemComponent* GetTDWTestAbilitySystemComponent()
		const { return AbilitySystemComponent; }
	
public:
	/** Sets default values for this character's properties */
	ATDWTestPlayerState();

	/**
	* The pawn data contains information on abilities, attributes and gameplay
	* effects to apply to the current pawn. As the current pawn has its ASC
	* created here, we assign the pawn data to the player state.
	*
	* @param PawnData The pawn data to give to this player state's ASC.
	*/
	void SetPawnData(const TObjectPtr<class UPawnData>& PawnData);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UTDWTestAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<class UPawnData> CurrentPawnData;
};
