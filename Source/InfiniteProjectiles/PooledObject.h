// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawn, APooledObject*, PoolActor);

UCLASS()
class INFINITEPROJECTILES_API APooledObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APooledObject();

	FOnPooledObjectDespawn OnPooledObjectDespawn;
	
	UFUNCTION(BlueprintCallable, Category = "Pooled Object")
		void Deactivate();

	
	void SetActive(bool isActive, FVector InitialVelocity = FVector::ZeroVector, float InitialSpeed = 0.0f, float MaxSpeed = 0.0f);
	void SetLifeSpan(float LifeTime);
	void SetPoolIndex(int Index);
	void SetPoolTag(FName Tag);


	bool IsActive();
	int GetPoolIndex();
	FName GetPoolTag();

	virtual void OnPoolBegin(FVector InitialVelocity, float InitialSpeed, float MaxSpeed);
	virtual void OnPoolEnd();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool Active;
	float LifeSpan = 0.0f;
	int PoolIndex;
	FName PoolTag;

	FTimerHandle LifeSpanTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
