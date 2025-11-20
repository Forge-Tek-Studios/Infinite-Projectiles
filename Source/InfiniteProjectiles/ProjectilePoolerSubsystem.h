// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PooledObject.h"
#include "ProjectilePoolerSubsystem.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig)
class INFINITEPROJECTILES_API UProjectilePoolerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	UFUNCTION(BlueprintCallable, Category = "Pooling")
	APooledObject* SpawnPooledObject();

	// UPROPERTY(Config, EditAnywhere, Category = "Pooling")
	UPROPERTY(Config, EditAnywhere, Category = "Pooling", meta = (MustImplement = "/Script/InfiniteProjectiles.PooledObject"))
	TSubclassOf<class APooledObject> PooledObjectSubclass;

	UPROPERTY(Config, EditAnywhere, Category = "Pooling")
	int PoolSize = 20;

	UPROPERTY(Config, EditAnywhere, Category = "Pooling")
	float PooledObjectLifeSpan = 3.0f;

	UFUNCTION()
	void OnPooledObjectDespawn(APooledObject* PoolActor);

private:
	TArray<APooledObject*> ObjectPool;
	TArray<int32> SpawnedPoolIndexes;
	
};