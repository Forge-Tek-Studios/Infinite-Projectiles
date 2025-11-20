// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePoolerSubsystem.h"
#include "PooledObject.h"
#include "ProjectilePoolerSettings.h"

void UProjectilePoolerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UProjectilePoolerSettings* PoolerSettings = GetDefault<UProjectilePoolerSettings>();
	if (PoolerSettings == nullptr)
	{
		return;
	}

	PooledObjectLifeSpan = PoolerSettings->PooledObjectLifeSpan;
	const int32 PoolSize = PoolerSettings->PoolSize;
	const TSubclassOf<class APooledObject> PooledObjectSubclass = PoolerSettings->PooledObjectClass;

	if (PooledObjectSubclass != nullptr)
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			for (int i = 0; i < PoolSize; ++i)
			{
				APooledObject* PooledObj = World->SpawnActor<APooledObject>(PooledObjectSubclass, FVector::ZeroVector, FRotator::ZeroRotator);
				if (PooledObj != nullptr)
				{
					PooledObj->SetActive(false);
					PooledObj->SetPoolIndex(i);
					PooledObj->OnPooledObjectDespawn.AddDynamic(this, &UProjectilePoolerSubsystem::OnPooledObjectDespawn);
					ObjectPool.Add(PooledObj);
				}
			}
		}
	}
}

void UProjectilePoolerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	ObjectPool.Empty();
}

APooledObject* UProjectilePoolerSubsystem::SpawnPooledObject()
{
	for (APooledObject* PooledObj : ObjectPool)
	{
		if (PooledObj != nullptr && !PooledObj->IsActive())
		{
			PooledObj->TeleportTo(FVector::ZeroVector, FRotator::ZeroRotator);
			PooledObj->SetLifeSpan(PooledObjectLifeSpan);
			PooledObj->SetActive(true);
			return PooledObj;
		}
	}

	// If no inactive objects are available, return nullptr.
	// This is safer than reusing an active object.
	return nullptr;
}

void UProjectilePoolerSubsystem::OnPooledObjectDespawn(APooledObject* PoolActor)
{
	// The object is already deactivated at this point,
	// so we don't need to do anything else here.
	// The object is now available to be spawned again.
}