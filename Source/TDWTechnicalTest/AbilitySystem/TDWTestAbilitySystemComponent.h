// Copyright Saulo Soares. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TDWTestAbilitySystemComponent.generated.h"

/**
* The project's AbilitySystemComponent. Mainly processes player input that
* are bound to gameplay abilities.
*
* The flow here is simple: When an input action is pressed, we get the input tag
* (a gameplay tag) "bound" to it by designer. In the callback, we notify this
* ASC that an ability input tag has been pressed/released. Then, during each
* frame, during input processing, the ASC checks which input tags are pressed/
* held or were released during this frame, and act accordingly.
*
* As during "ASC->GiveAbility()" we add an input tag to the GA, we can match the
* input action input tag with the tag attributed to the GA. Thus, we form a
* bound between the input action and the GA by tags.
*/
UCLASS()
class TDWTECHNICALTEST_API UTDWTestAbilitySystemComponent :
	public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UTDWTestAbilitySystemComponent();
	
public:
	/**
	* Called at each frame. Checks which input tags are pressed/held or were
	* released during this frame and act accordingly. For pressed/held input
	* tags, we may either try to activate the ability or send "input pressed"
	* event to it. For released input tags, we may send "input released" event
	* to it.
	*
	* The input tags are sent by the input handler when an input action is
	* pressed or released. As those input actions are "bound" to input tags,
	* they are sent to this ASC. As GAs have matching input tags inside, we can
	* find which GA we are processing by the pressed/released/held input tag.
	*/
	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	
	/**
	* Called when an ability has its input pressed. Will send "input pressed"
	* event to it manually.
	*
	* @param Spec The ability's spec that had its input pressed.
	*/
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;

	/**
	* Called when an ability has its input released. Will send "input released"
	* event to it manually.
	*
	* @param Spec The ability's spec that had its input released.
	*/
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;
	
	void ClearAbilityInput();

	/**
	* Called when an ability input tag has been pressed. This is sent by the
	* input handler, which received a callback from an input action press. By
	* receiving the input tag, we can (try to) find the ability that contains
	* the matching input tag inside (which is attributed on ASC->GiveAbility()).
	*
	* By caching the input tag pressed, it gets processed during the next frame
	* on "ProcessAbilityInput()", and will try to activate or send "input
	* pressed" event to the ability.
	*/
	void AbilityInputTagPressed(const FGameplayTag& InputTag);

	/**
	* Called when an ability input tag has been released. This is sent by the
	* input handler, which received a callback from an input action release. By
	* receiving the input tag, we can (try to) find the ability that contains
	* the matching input tag inside (which is attributed on ASC->GiveAbility()).
	*
	* By caching the input tag released, it gets processed during the next frame
	* on "ProcessAbilityInput()", and will send "input released" event to the
	* ability (if active).
	*/
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
protected:
	/** Handles to abilities that had their input pressed this frame. */
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	/** Handles to abilities that had their input released this frame. */
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

	/** Handles to abilities that have their input held. */
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
};
