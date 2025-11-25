// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledObject.h"

// Sets default values
APooledObject::APooledObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


#include "Components/PrimitiveComponent.h"

// ... (rest of the file) ...

void APooledObject::OnPoolBegin(FVector InitialVelocity, float InitialSpeed, float MaxSpeed)
{
	// Base implementation, can be overridden by subclasses
	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);
	for (UPrimitiveComponent* Component : PrimitiveComponents)
	{
		Component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void APooledObject::OnPoolEnd()
{
	// Base implementation, can be overridden by subclasses
	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);
	for (UPrimitiveComponent* Component : PrimitiveComponents)
	{
		Component->SetSimulatePhysics(false);
		Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APooledObject::SetActive(bool isActive, FVector InitialVelocity, float InitialSpeed, float MaxSpeed)
// ... (rest of the file) ...
{
	Active = isActive;
	SetActorHiddenInGame(!isActive);
	
	if (isActive)
	{
		OnPoolBegin(InitialVelocity, InitialSpeed, MaxSpeed);
		if (PoolLifeSpan > 0.0f)
		{
			GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &APooledObject::Deactivate, PoolLifeSpan, false);
		}
	}
	else
	{
		OnPoolEnd(); // Call OnPoolEnd when deactivated
	}
}

void APooledObject::SetPoolLifeSpan(float LifeTime)
{
	PoolLifeSpan = LifeTime;
}

void APooledObject::SetPoolIndex(int Index)
{
	PoolIndex = Index;
}

void APooledObject::SetPoolTag(FName Tag)
{
	PoolTag = Tag;
}

void APooledObject::Deactivate()
{
	SetActive(false, FVector::ZeroVector, 0.0f, 0.0f);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledObjectDespawn.Broadcast(this);
}
bool APooledObject::IsActive()
{
	return Active;
}

int APooledObject::GetPoolIndex()
{
	return PoolIndex;
}

FName APooledObject::GetPoolTag()
{
	return PoolTag;
}



//DEFAULT FUNCTIONS
void APooledObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APooledObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

