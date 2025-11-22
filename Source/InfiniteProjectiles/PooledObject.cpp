// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledObject.h"

// Sets default values
APooledObject::APooledObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void APooledObject::OnPoolBegin(FVector InitialVelocity)
{
	// Base implementation, can be overridden by subclasses
}

void APooledObject::OnPoolEnd()
{
	// Base implementation, can be overridden by subclasses
}

void APooledObject::SetActive(bool isActive, FVector InitialVelocity)
{
	Active = isActive;
	SetActorHiddenInGame(!isActive);
	
	if (isActive)
	{
		OnPoolBegin(InitialVelocity); // Call OnPoolBegin when activated
		if (LifeSpan > 0.0f)
		{
			GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &APooledObject::Deactivate, LifeSpan, false);
		}
	}
	else
	{
		OnPoolEnd(); // Call OnPoolEnd when deactivated
	}
}

void APooledObject::SetLifeSpan(float LifeTime)
{
	LifeSpan = LifeTime;
}

void APooledObject::SetPoolIndex(int Index)
{
	PoolIndex = Index;
}

void APooledObject::Deactivate()
{
	SetActive(false, FVector::ZeroVector);
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

