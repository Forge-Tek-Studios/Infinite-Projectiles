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

	
	void SetActive(bool isActive);
	void SetLifeSpan(float LifeTime);
	void SetPoolIndex(int Index);


	bool IsActive();
	int GetPoolIndex();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool Active;
	float LifeSpan = 0.0f;
	int PoolIndex;

	FTimerHandle LifeSpanTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
