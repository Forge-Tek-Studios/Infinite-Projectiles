// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PooledObject.h"
#include "InfiniteProjectilesProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game, Blueprintable, BlueprintType)
class AInfiniteProjectilesProjectile : public APooledObject
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	/** If true, the projectile will be returned to the pool on blocking hit. If false, it will bounce or pass through until its lifespan expires. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool bDestroyOnHit = true;

	AInfiniteProjectilesProjectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Override the pooled object lifecycle functions
	virtual void OnPoolBegin(FVector InitialVelocity, float InitialSpeed, float MaxSpeed) override;
	virtual void OnPoolEnd() override;

	virtual void Destroyed() override;

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

