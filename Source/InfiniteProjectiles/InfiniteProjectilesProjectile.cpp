// Copyright Epic Games, Inc. All Rights Reserved.

#include "InfiniteProjectilesProjectile.h"
#include "InfiniteProjectiles.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AInfiniteProjectilesProjectile::AInfiniteProjectilesProjectile() 
{
	UE_LOG(LogInfiniteProjectiles, Warning, TEXT("Projectile CONSTRUCTED: %s"), *GetName());

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AInfiniteProjectilesProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 0.0f; // Initialized to 0.0f, will be set by OnPoolBegin
	ProjectileMovement->MaxSpeed = 0.0f;    // Initialized to 0.0f, will be set by OnPoolBegin
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->bAutoActivate = false;

	// Disable engine-level auto-destruction
	InitialLifeSpan = 0.0f;
}

void AInfiniteProjectilesProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}

	if (bDestroyOnHit)
	{
		Deactivate();
	}
}

void AInfiniteProjectilesProjectile::OnPoolBegin(FVector InitialVelocity, float InitialSpeed, float MaxSpeed)
{
	Super::OnPoolBegin(InitialVelocity, InitialSpeed, MaxSpeed);
	UE_LOG(LogInfiniteProjectiles, Warning, TEXT("Projectile POOL BEGIN: %s"), *GetName());
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProjectileMovement->SetUpdatedComponent(CollisionComp); // Ensure updated component is set

	ProjectileMovement->InitialSpeed = InitialSpeed;
	ProjectileMovement->MaxSpeed = MaxSpeed;

	ProjectileMovement->Activate(true);
	ProjectileMovement->Velocity = InitialVelocity;
}

void AInfiniteProjectilesProjectile::OnPoolEnd()
{
	Super::OnPoolEnd();
	UE_LOG(LogInfiniteProjectiles, Warning, TEXT("Projectile POOL END: %s"), *GetName());

	// Stop any physics simulation on the collision component
	CollisionComp->SetSimulatePhysics(false);
	// Disable all collision
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Stop movement and reset velocity
	ProjectileMovement->Velocity = FVector::ZeroVector;
	// Deactivate the component so it doesn't tick
	ProjectileMovement->Deactivate();

	// Move the actor far away and out of sight
	SetActorLocation(FVector(0.f, 0.f, 0.f));
}

void AInfiniteProjectilesProjectile::Destroyed()
{
	Super::Destroyed();
	UE_LOG(LogInfiniteProjectiles, Error, TEXT("Projectile DESTROYED: %s"), *GetName());
}