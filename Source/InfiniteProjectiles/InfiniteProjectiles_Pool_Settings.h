// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "PooledObject.h"
#include "InfiniteProjectiles_Pool_Settings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta=(DisplayName="Infinite Projectiles Pool Settings"))
class INFINITEPROJECTILES_API UInfiniteProjectiles_Pool_Settings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Pooling")
	TSubclassOf<class APooledObject> PooledObjectClass;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Pooling", meta = (ClampMin = 1, ClampMax = 200))
	int PoolSize = 20;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Pooling", meta = (ClampMin = 0.0))
	float PooledObjectLifeSpan = 3.0f;
	
};
