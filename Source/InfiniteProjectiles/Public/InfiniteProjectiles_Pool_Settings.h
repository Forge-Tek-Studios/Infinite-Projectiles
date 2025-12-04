// Copyright Forge Tek Studios LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "PooledObject.h"
#include "ProjectilePoolSettings.h"
#include "InfiniteProjectiles_Pool_Settings.generated.h"


UCLASS(Config=Game, defaultconfig, meta=(DisplayName="Infinite Projectiles Pool Settings"))
class INFINITEPROJECTILES_API UInfiniteProjectiles_Pool_Settings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Pooling")
	TArray<FProjectilePoolSettings> ProjectilePools;
	
};
