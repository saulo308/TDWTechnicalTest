// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "TDWTechnicalTestCharacterBase.h"
#include "EnemyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStunTagChanged);

/**
* The base character class for enemies. In contrast with player, the enemy
* creates its ASC here, as when character is dead, we can clear any logic from
* his ASC. Any other instance of the enemy will be a completely new instance.
*
* Also implements a simple stun logic, for demonstration.
*/
UCLASS()
class TDWTECHNICALTEST_API AEnemyCharacter : public ATDWTechnicalTestCharacterBase,
	public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	/** Sets default values for this character's properties */
	AEnemyCharacter();

public:
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
public:
	/** Called every frame */
	virtual void Tick(float DeltaTime) override;
	
	/**
	* Called once the Character is possessed (by AIController). Will initialize
	* the character's ASC.
	*/
	virtual void PossessedBy(AController* NewController) override;
	
protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

private:
	/**
	* Called when the stun tag has been changed on the character's ASC.
	* 
	* This will simply broadcast "OnStunTagChanged" so BP knows when character
	* has its stun state updated, implementing a simple logic for stun.
	*/
	UFUNCTION()
	void OnStunTagChangedCallback(const FGameplayTag Tag, int32 NewCount);

private:
	/**
	* Initializes the ASC. Will call "InitAbilityActorInfo" on it, passing the
	* PlayerState as owner and the Character as the avatar.
	*/
	void InitAbilitySystemComponent();
	
	/**
	* The pawn data contains information on abilities, attributes and gameplay
	* effects to apply to the current pawn. As the current pawn has its own ASC
	* created here, we assign the pawn data here, in contrast with player, that
	* sets it on his player state.
	*
	* @param PawnData The pawn data to give to this character's ASC.
	*/
	void SetPawnData(const TObjectPtr<class UPawnData>& PawnData);

public:
	/**
	* Called when the stun tag has changed on the ASC (created or removed).
	* Thus, indicates if the character is stunned or not.
	*/
	UPROPERTY(BlueprintAssignable)
	FOnStunTagChanged OnStunTagChanged;
	
protected:
	/**
	* The pawn data contains information on abilities, attributes and gameplay
	* effects to apply to the pawn; as well as input config. Can be seen as
	* "initial abilities, attributes and GEs" to give to the owning pawn. The
	* ability set will be given after ASC initialization.
	*
	* As enemy does not handle input, input data from pawn data will be
	* ignored.
	*
	* @note SoftObjectPtr as it may reference many assets.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		Category="TDWTestCharacter|PawnData")
	TSoftObjectPtr<class UPawnData> DefaultPawnData;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UTDWTestAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<class UPawnData> CurrentPawnData;
};
