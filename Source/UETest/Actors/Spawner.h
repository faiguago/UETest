// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Data/ItemsToSpawnDataAsset.h"
#include "Spawner.generated.h"

UCLASS()
class UETEST_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = Spawner)
	AActor* SpawnVolume;

	UPROPERTY(EditAnywhere, Category = Spawner)
	UItemsToSpawnDataAsset* ItemsToSpawn;

private:

	void SpawnItems();
};
