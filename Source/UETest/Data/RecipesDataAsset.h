// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.h"
#include "RecipesDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FRecipeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Recipe)
	TArray<EItemType> Recipe;

	UPROPERTY(EditAnywhere, Category = Recipe)
	TArray<UItemDataAsset*> ProbableResults;

public:

	const TArray<UItemDataAsset*>& GetProbableResults() const
	{
		return ProbableResults;
	}

	const TArray<EItemType>& GetRecipe() const
	{
		return Recipe;
	}
};

/**
 * 
 */
UCLASS()
class UETEST_API URecipesDataAsset : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FRecipeData> Recipes;

public:

	const TArray<FRecipeData>& GetRecipes()
	{
		return Recipes;
	}
};
