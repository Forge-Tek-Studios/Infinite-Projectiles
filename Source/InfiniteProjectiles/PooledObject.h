// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledObject.generated.h"

UCLASS()
class INFINITEPROJECTILES_API APooledObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APooledObject();

	void SetActive(bool isActive);
	void SetLifeSpan(float, LifeTime);
	void SetPoolIndex(int Index);

	bool IsActive();
	int GetPoolIndex();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool Active;
	float LifeSpan = 0.0f;
	int PoolIndex;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
