// Copyright Forge Tek Studios LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PooledObject.h"
#include "ProjectilePoolSettings.h"
#include "InfiniteProjectilesSubsystem.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig)
class INFINITEPROJECTILES_API UInfiniteProjectilesSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	UFUNCTION(BlueprintCallable, Category = "Pooling", meta = (AutoCreateRefTerm = "InitialVelocity"))
	APooledObject* SpawnPooledObject(FName PoolTag, const FTransform& SpawnTransform, const FVector& InitialVelocity, float InitialSpeed, float MaxSpeed);

	// UPROPERTY(Config, EditAnywhere, Category = "Pooling")
	UFUNCTION()
	void OnPooledObjectDespawn(APooledObject* PoolActor);

private:
	UPROPERTY()
	TMap<FName, FProjectilePool> ObjectPools;
	
};