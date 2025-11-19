// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePooler.h"

// Sets default values for this component's properties
UProjectilePooler::UProjectilePooler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProjectilePooler::BeginPlay()
{
	Super::BeginPlay();

	if (PooledObjectSubclass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				APooledObject* PooledObj = World->SpawnActor<APooledObject>(PooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
				if (PooledObj != nullptr)
				{
					PooledObj->SetActive(false);
					PooledObj->SetPoolIndex(i);
					PooledObj->OnPooledObjectDespawn.AddDynamic(this, &UProjectilePooler::OnPooledObjectDespawn);
					ObjectPool.Add(PooledObj);
				}
			}
		}
	}
	
}

APooledObject* UProjectilePooler::SpawnPooledObject()
{
	for (int i = 0; i < ObjectPool.Num(); i++)
	{
		if (!SpawnedPoolIndices.Contains(i))
		{
			APooledObject* PooledObj = ObjectPool[i];
			if (PooledObj)
			{
				PooledObj->SetLifeSpan(PooledObjectLifeSpan);
				PooledObj->SetActorHiddenInGame(false);
				PooledObj->SetActorEnableCollision(true);
				SpawnedPoolIndices.Add(i);
				return PooledObj;
			}
		}
	}
	return nullptr;
}

void UProjectilePooler::OnPooledObjectDespawn(APooledObject* PoolActor)
{
	int Index = ObjectPool.IndexOfByKey(PoolActor);
	if (Index != INDEX_NONE)
	{
		SpawnedPoolIndices.Remove(Index);
		PoolActor->SetActorHiddenInGame(true);
		PoolActor->SetActorEnableCollision(false);
	}
}


// Called every frame
void UProjectilePooler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

