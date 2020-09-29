// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Data/RecipesDataAsset.h"
#include "Cooker.generated.h"

class UBoxComponent;
class AItem;
class UArrowComponent;

UCLASS()
class UETEST_API ACooker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACooker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Recipes)
	int32 MinItemsToActivateCooker = 2;

	UPROPERTY(EditAnywhere, Category = Recipes)
	URecipesDataAsset* RecipesDataAsset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Cook();

	void SpawnItem(UItemDataAsset* ItemDataAssetToCook);

private:

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Trigger;

	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* LocationToSpawnNewItem;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ButtonToCook;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* InOverlappedComponent, AActor* InOtherActor, UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex, bool InbFromSweep, const FHitResult& InSweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* InOverlappedComponent, AActor* InOtherActor, UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex);

	UPROPERTY()
	TArray<AItem*> ItemsToCook;

	UPROPERTY()
	TArray<EItemType> ItemsType;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicButtonMaterial;

	void UpdateButtonState();

	UItemDataAsset* AnalizeRecipe(const FRecipeData& Recipe);

private:

	bool bCanCook;

	bool bIsCooking;

};
