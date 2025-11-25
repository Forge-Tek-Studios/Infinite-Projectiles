#include "InfiniteProjectilesSubsystem.h"
#include "PooledObject.h"
#include "InfiniteProjectiles_Pool_Settings.h"
#include "ProjectilePoolSettings.h"
#include "InfiniteProjectilesProjectile.h" // Required for casting to AInfiniteProjectilesProjectile

void UInfiniteProjectilesSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    const UInfiniteProjectiles_Pool_Settings* PoolerSettings = GetDefault<UInfiniteProjectiles_Pool_Settings>();
    if (PoolerSettings == nullptr)
    {
        return;
    }

    UWorld* World = GetWorld();
    if (World != nullptr)
    {
        for (const FProjectilePoolSettings& PoolSettings : PoolerSettings->ProjectilePools)
        {
            FProjectilePool NewPool;
            for (int i = 0; i < PoolSettings.PoolSize; ++i)
            {
                APooledObject* PooledObj = World->SpawnActor<APooledObject>(PoolSettings.PooledObjectClass, FVector::ZeroVector, FRotator::ZeroRotator);
                if (PooledObj != nullptr)
                {
                    PooledObj->SetActive(false, FVector::ZeroVector);
                    PooledObj->SetPoolIndex(i);
                    PooledObj->SetPoolTag(PoolSettings.PoolTag);
                    PooledObj->SetPoolLifeSpan(PoolSettings.PooledObjectLifeSpan); // Set the lifespan here
                    PooledObj->OnPooledObjectDespawn.AddDynamic(this, &UInfiniteProjectilesSubsystem::OnPooledObjectDespawn);
                    NewPool.Pool.Add(PooledObj);
                }
            }
            ObjectPools.Add(PoolSettings.PoolTag, NewPool);
        }
    }
}

void UInfiniteProjectilesSubsystem::Deinitialize()
{
    Super::Deinitialize();
    ObjectPools.Empty();
}

APooledObject* UInfiniteProjectilesSubsystem::SpawnPooledObject(FName PoolTag, const FTransform& SpawnTransform, const FVector& InitialVelocity, float InitialSpeed, float MaxSpeed)
{
    if (!ObjectPools.Contains(PoolTag))
    {
        return nullptr;
    }

    FProjectilePool& Pool = ObjectPools[PoolTag];
    for (APooledObject* PooledObj : Pool.Pool)
    {
        if (PooledObj != nullptr && !PooledObj->IsActive())
        {
            PooledObj->SetActorTransform(SpawnTransform);

            // The lifespan is already set on the PooledObj during initialization,
            // so no need to look it up here again.
            
            // Apply the SpawnTransform's rotation to the InitialVelocity
            FVector RotatedVelocity = SpawnTransform.GetRotation().RotateVector(InitialVelocity);

            // All pooled objects are now activated via SetActive, which handles visibility and calls OnPoolBegin internally.
            PooledObj->SetActive(true, RotatedVelocity, InitialSpeed, MaxSpeed);

            return PooledObj;
        }
    }

    // If no inactive objects are available, return nullptr.
    return nullptr;
}

void UInfiniteProjectilesSubsystem::OnPooledObjectDespawn(APooledObject* PoolActor)
{
    // The object is already deactivated at this point,
    // so we don't need to do anything else here.
    // The object is now available to be spawned again.
}