// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Data/ItemDataAsset.h"
#include "Item.generated.h"

UCLASS()
class UETEST_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init(const FItemData& InItemData);

	void UpdateFresnel(float InValue);

	void UpdatePhysicsState(bool InNewState);

	bool GetIsGrabbable()
	{
		return bIsGrabbable;
	}

	EItemType GetItemType()
	{
		return ItemType;
	}

private:

	bool bIsGrabbable;

	EItemType ItemType;

	UPROPERTY()
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;
};
