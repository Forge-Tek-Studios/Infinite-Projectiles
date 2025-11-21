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
	UFUNCTION()
	void OnPooledObjectDespawn(APooledObject* PoolActor);

private:
	TArray<APooledObject*> ObjectPool;
	float PooledObjectLifeSpan;
	
};