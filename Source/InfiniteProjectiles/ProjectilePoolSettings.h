// Copyright Forge Tek Studios LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "PooledObject.h"
#include "ProjectilePoolSettings.generated.h"

USTRUCT(BlueprintType)
struct FProjectilePoolSettings
{
    GENERATED_BODY()

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Pooling")
    FName PoolTag;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Pooling")
    TSubclassOf<class APooledObject> PooledObjectClass;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Pooling", meta = (ClampMin = 1, ClampMax = 200))
    int PoolSize = 20;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Pooling", meta = (ClampMin = 0.0))
    float PooledObjectLifeSpan = 3.0f;
};

USTRUCT(BlueprintType)
struct FProjectilePool
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<APooledObject*> Pool;
};
