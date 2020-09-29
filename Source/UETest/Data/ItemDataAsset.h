// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Item_A,
	Item_B,
	Item_C,
	Item_D,
	Item_E,
	Item_F
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Item)
	bool bIsGrabbable;

	UPROPERTY(EditAnywhere, Category = Item)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = Item)
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, Category = Item)
	UMaterialInterface* MaterialToSet;

	UPROPERTY(EditAnywhere, Category = Item)
	FVector WorldScale = FVector::OneVector;
};

/**
 *
 */
UCLASS()
class UETEST_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Item)
	FItemData Item;

public:

	const FItemData& GetItem()
	{
		return Item;
	}
};
