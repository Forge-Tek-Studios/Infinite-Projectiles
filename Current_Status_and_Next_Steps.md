# Projectile Pooler Refactor: Status and Next Steps

## High-Level Goal
The primary objective is to refactor the existing object pooling system to correctly handle spawning `AInfiniteProjectilesProjectile` actors. The requirements are:
- Allow projectiles to be spawned with a specific `FTransform` (location, rotation, scale).
- Allow projectiles to be spawned with a specific `FVector` initial velocity.
- Ensure that when projectiles are inactive in the pool, their physics and collision are disabled to prevent unwanted simulation.

## Current Unresolved Issue
The pool is now being correctly populated with `BP_MyProjectile` instances at game start. However, approximately one second after starting the game, all the inactive projectiles in the pool are automatically destroyed and disappear from the World Outliner.

## What We Have Tried So Far

1.  **Incorrect Configuration:** We initially had a configuration conflict where settings in `DefaultGame.ini` were overriding the settings in the "Project Settings" UI.
    -   **Result:** This was **fixed**. We consolidated all configuration into the **Project Settings -> Game -> Projectile Pooler Settings** menu, and the pool now populates correctly upon startup.

2.  **Engine-Level Actor Destruction (`InitialLifeSpan`):** We hypothesized that the engine was automatically destroying the actors because their `InitialLifeSpan` property was set to a non-zero value by default.
    -   **Action:** We explicitly set `InitialLifeSpan = 0.0f;` in the `AInfiniteProjectilesProjectile` constructor.
    -   **Result:** This did **not** solve the problem. The actors are still being destroyed.

3.  **Disabling Physics in Pool:** We implemented the `OnPoolEnd()` function for the projectile to disable its collision component and deactivate its projectile movement component. This should prevent the inactive projectiles from falling through the world or interacting with anything.
    -   **Result:** This logic appears correct but has not prevented the actors from being destroyed, suggesting the cause of destruction is not physics-based.

## Current Strategy: Debugging with Logs
Since the direct fixes have not worked, we have shifted to active debugging to trace the projectile's lifecycle.

1.  **Code Changes:** I have injected `UE_LOG` messages into all key lifecycle functions of the `AInfiniteProjectilesProjectile` class:
    -   **Constructor:** Logs when a projectile is created.
    -   **`OnPoolEnd()`:** Logs when a projectile is returned to the pool (or initialized into it).
    -   **`Destroyed()`:** Logs with an **ERROR** message when the engine destroys the projectile for **any reason**. This is the most critical log message for our investigation.

2.  **Status:** We just finished adding the necessary code to declare and define the custom log category (`LogInfiniteProjectiles`), which fixed the final set of compilation errors. The project should now compile successfully.

## Next Step
When you are ready to resume, the immediate next step is:

1.  **Compile** the project in the Unreal Engine editor.
2.  Open the **Output Log** window (`Window -> Developer Tools -> Output Log`).
3.  **Play in Editor**.
4.  Wait for the projectiles to disappear from the Outliner.
5.  **Copy the entire contents of the Output Log and provide it to me.** The log messages, especially the red "Projectile DESTROYED" error message, will tell us exactly what is causing the deletion.
