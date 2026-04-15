# The Dark West Technical Test
Saulo Soares


# How to Use  
  
- **W / A / S / D** — Character movement  
- **E** — Executes *Leap Slam* toward the mouse cursor (only if within the minimum required distance)  
- **R** — Toggles ability trace debugging


# General Aspects

- This project was implemented as a single-player experience. Since *The Dark West* appears to be a single-player game, the goal was to stay as aligned as possible with the expected context of this position. Additionally, because the implementation involves random number generation and setting actor location manually, replication concerns were intentionally set aside in favor of focusing on system design, which I think is more relevant for evaluation in this role.

- The project uses CVars to control ability trace debugging. Pressing **R** triggers a debug key event in the player character, executing the console command `ability.debug.traceAbility 0` or `ability.debug.traceAbility 1` (toggle). This key binding exists for demonstration purposes only—developers are expected to use the console command directly during development.

- The leap target location is dynamically calculated based on the player's intended destination. First, the system enforces a square range constraint, as defined in the PoE wiki. Any attempt to leap beyond the maximum allowed distance (configurable by the designer) is clamped within this range. Additionally, the Gameplay Ability (GA) evaluates collisions with static and dynamic obstacles (e.g., walls) as well as invalid areas (e.g., void/skybox). In such cases, the target location is adjusted so the character lands at the furthest valid point without intersecting geometry (at the final position) or falling out of the world.

- No animations were imported into the project. However, animation integration was considered, and implementation notes were added within the `GA_LeapSlam` Blueprint to outline how animations would be handled.

- The Leap Slam attack speed formula described in the PoE wiki depends on weapon data (e.g., weapon type and attack speed). As a weapon system was outside the scope of this test (I decided that), the duration calculation was simplified. It is implemented as a Blueprint method within `GA_LeapSlam`, allowing designers to easily iterate and replace it with a more accurate formula if needed.

- The current leap behavior does not exactly match *Path of Exile*. The reference used was:   
 [Path of Exile - Leap Slam skill](https://youtu.be/ZYyuGKgCU_w?si=tDntGk1od6hV2oFw). This difference is intentional. The leap motion is entirely driven by **float curves** that control horizontal and vertical acceleration over time, allowing the “feel” of the ability to be easily adjusted without modifying code. The curves can be found in: `Content/Data/AbilityData/LeapSlam`. By editing these curves (keeping the X-axis normalized within the **[0,1]** range), designers can quickly prototype and iterate on different movement profiles, achieving a wide variety of behaviors with minimal effort. This approach further reinforces the data-driven architecture adopted in this project, demonstrating how gameplay feel can be tuned directly through data rather than hardcoded logic.

- The stun implementation is intentionally simple. It is applied as a Gameplay Tag to the target’s Ability System Component (ASC). Since the enemy used in this test is a dummy, the effect is represented by a simple text update displayed above its head. This implementation was designed to demonstrate the stun behavior described in the PoE wiki—applying a 100% chance to stun when the target is at full health, and a probabilistic chance otherwise.

# Architecture

The project was implemented following two main architectural approaches: **Data-Driven Architecture** and **MVVM**.

## Data-Driven Architecture

As *The Dark West* seems (for me) to be the type of game where designers are expected to continuously iterate on balance (items, abilities, attributes, etc.), I leveraged one of Unreal Engine’s greatest strengths: a data-driven architecture.

The core idea behind this approach is to implement foundational systems in C++, while exposing configurable elements to designers through data assets. This allows designers to iterate quickly on aspects such as meshes, VFX, animations, and gameplay parameters without requiring code changes. As a result, iteration time is reduced, technical bottlenecks are minimized, and designers are empowered to experiment and balance the game more efficiently.

In this project, a key example of this approach is the use of `UAbilityData` and `UAbilityData_Fragment`.

- `UAbilityData` is a data asset passed to Gameplay Abilities (GAs), containing combat-related data such as mana cost, damage, and cooldown duration.
- Each `UAbilityData` is composed of multiple `UAbilityData_Fragment` objects, where each fragment encapsulates a specific aspect of the ability (e.g., mana cost, damage, stun effect).

This composition-based design enables scalability and flexibility. Designers can set data for  new abilities simply by assembling different fragments, without modifying code (e.g., not having to create a .cpp data asset that inherits from `UAbilityData` for each ability). 

Additionally, this architecture opens the possibility for more generic Gameplay Abilities. For example, instead of implementing a specific `GA_LeapSlam`, we could define a generic `GA_Leap`. The final behavior of the ability would then be entirely determined by the fragments assigned to its `UAbilityData`.

This would allow multiple variations—such as:
- A damaging leap (Leap Slam)
- A defensive leap (Leap Shield)
- A movement-only leap
- A zero-cost leap

all driven by a single GA implementation. The GA would simply check for the presence of specific fragments to determine its behavior (e.g., applying damage on landing). While powerful, this approach was intentionally not fully implemented to avoid overengineering the solution for the scope of this test.

This design philosophy was also extended to other systems:
- Use of `BPFunctionLibrary` for shared logic
- Generic Gameplay Effects (GE) for cost and cooldown, implemented using MMCs and `UGameplayEffectExecutionCalculation`, allowing reuse

Overall, the system was designed with extensibility and scalability as primary goals.

## MVVM

The project also adopts the **MVVM (Model-View-ViewModel)** pattern to decouple gameplay logic from UI.

Unreal Engine provides native support for MVVM through a plugin that allows UMG widgets to bind directly to ViewModels. In this pattern:
- The **Model** represents gameplay data and logic
- The **ViewModel** acts as an intermediary, exposing data to the UI
- The **View** (UMG widgets) binds to the ViewModel

The main benefit of this approach is that UI updates become event-driven. UMG widgets react only when the ViewModel notifies changes, improving performance and maintainability.

In this project, MVVM was implemented for the player’s **vital attributes** (health and mana). The gameplay systems update the ViewModel with the latest values, while the UI reads directly from it.

This ensures:
- Gameplay systems remain agnostic of UI implementation
- UI components remain agnostic of gameplay logic

The pattern is used for:
- The player HUD (health and mana bars)
- Enemy health bars, implemented using `UWidgetComponent` to render UI elements in the world space above characters

This results in a clean separation of concerns and a more maintainable UI architecture.


# Input

One of the first steps in this project was integrating an input-to-ability binding system that I have been using in another project.

The core idea is to decouple input handling from specific ability implementations by introducing **Input Tags**. Input Actions are mapped to designer-defined Gameplay Tags (referred to as *Input Tags* in the codebase). These same tags are also assigned to Gameplay Abilities (GAs) when they are granted to the Ability System Component (ASC), using dynamic tags.

This creates a flexible and data-driven binding between player input and abilities.

### Flow Overview

1. **Input Action Triggered**  
   When an input action is pressed or released, the system resolves which **Input Tag** is associated with that action.
2. **Tag Dispatching**  
   The Input Tag is forwarded to a custom implementation of the **Ability System Component (ASC)**.
3. **Frame-Based Processing**  
   The ASC caches input state changes and processes them on a per-frame basis. During each frame, it evaluates:
   - Input Tags that were **pressed**
   - Input Tags that are **held**
   - Input Tags that were **released**
4. **Ability Resolution**  
   Since Gameplay Abilities are also tagged with matching Input Tags, the ASC can:
   - Attempt to **activate abilities** when an input is pressed
   - Forward **input pressed/released events** to active abilities

This approach ensures a clean separation between input configuration and ability logic, allowing designers to easily remap inputs or reuse abilities without modifying code. It also scales well as new abilities and input schemes are introduced.

# Limitations & Future Work

Due to full-time work commitments, development on this test was limited to off-hours and weekend. As a result, some aspects were (unfortunately) intentionally left incomplete and would benefit from further iteration and polish.

1. **Leap Trajectory Validation**  
   The current leap target location system reliably ensures that the final position is valid (i.e., the character will not end up stuck or in an unreachable state, based on current testing). However, the validation is only performed at the destination point.  
   
   This means that during the leap, the character may pass through static or dynamic geometry, resulting in potential mesh clipping. A more robust solution would involve tracing the entire trajectory prior to execution, allowing the system to either:
   - Adjust the path dynamically, or  
   - Prevent the leap entirely if an invalid trajectory is detected  

2. **Debug Visualization Limitations**  
   The current debug trace visualization is only triggered when the ability is executed, showing information such as maximum distance and AoE radius. While functional, this approach limits iteration, as designers must deal with cooldowns, resource costs, and execution timing to test the ability.

   A more effective solution—planned but not implemented due to time constraints—would be real-time trajectory visualization. In this approach, the system would continuously render the predicted leap path based on the current mouse position.

   Since the trajectory calculation is already parameterized using a normalized **[0,1] alpha**, this feature could be implemented with relatively low overhead. It would significantly improve iteration speed, allowing designers to:
   - Rapidly evaluate the feel of the ability  
   - Identify problematic areas in the environment  
   - Detect inconsistencies or edge cases in trajectory behavior  