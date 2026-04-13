// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

/**
* 
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDWTECHNICALTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/** Sets default values for this component's properties */
	UHealthComponent();

public:	
	/** */
	UFUNCTION(BlueprintCallable, Category = "Health")
	void InitializeWithAbilitySystem(class UAbilitySystemComponent* InASC);

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** */
	virtual void HandleOutOfHealth();

private:
	/** */
	UPROPERTY()
	TObjectPtr<const class UVitalsSet> VitalsSet;
};
