// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "TDWTechnicalTestCharacterBase.h"
#include "EnemyCharacter.generated.h"

/**
* 
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
	/** */
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
public:
	/** Called every frame */
	virtual void Tick(float DeltaTime) override;
	
	/**
	* Called once the Character is possessed on the server. Will initialize
	* the ASC on the server.
	*/
	virtual void PossessedBy(AController* NewController) override;
	
protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

private:
	/**
	* Initializes the ASC. Will call "InitAbilityActorInfo" on it, passing the
	* PlayerState as owner and the Character as the avatar.
	*/
	void InitAbilitySystemComponent();
	
	/** */
	void SetPawnData(const TObjectPtr<class UPawnData>& PawnData);
	
protected:
	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		Category="TDWTestCharacter|PawnData")
	TSoftObjectPtr<class UPawnData> DefaultPawnData;
	
private:
	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UTDWTestAbilitySystemComponent> AbilitySystemComponent;
	
	/** */
	UPROPERTY()
	TObjectPtr<class UPawnData> CurrentPawnData;
};
