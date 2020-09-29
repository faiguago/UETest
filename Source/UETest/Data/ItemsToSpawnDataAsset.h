// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.h"
#include "ItemsToSpawnDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FItemToSpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Spawner)
	int32 QuantityToSpawn;

	UPROPERTY(EditAnywhere, Category = Spawner)
	UItemDataAsset* ItemData;
};

/**
 * 
 */
UCLASS()
class UETEST_API UItemsToSpawnDataAsset : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Spawner)
	TArray<FItemToSpawnData> ItemsToSpawn;

public:

	const TArray<FItemToSpawnData>& GetItemsToSpawn()
	{
		return ItemsToSpawn;
	}
};
