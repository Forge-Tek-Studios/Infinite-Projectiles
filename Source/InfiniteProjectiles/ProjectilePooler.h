// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PooledObject.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectilePooler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INFINITEPROJECTILES_API UProjectilePooler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectilePooler();

	UFUNCTION(BlueprintCallable, Category = "Pooling")
		APooledObject* SpawnPooledObject();	

	UPROPERTY(EditAnywhere, Category = "Pooling")
		TSubclassOf<class APooledObject> PooledObjectSubclass;
	
	UPROPERTY(EditAnywhere, Category = "Pooling")
		int PoolSize = 20;
	
	UPROPERTY(EditAnywhere, Category = "Pooling")
		float PooledObjectLifeSpan = 0.0f;

	UFUNCTION()
		void OnPooledObjectDespawn(APooledObject* PoolActor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<APooledObject*> ObjectPool;
	TArray<int> SpawnedPoolIndices;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
