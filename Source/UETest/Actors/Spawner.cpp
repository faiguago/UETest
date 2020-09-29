// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Item.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnItems();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnItems()
{
	if (!ItemsToSpawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Items To Spawn Is EMPTY!"));
		return;
	}

	UWorld* const World = GetWorld();
	if (!World)
		return;

	for (const auto& ItemToSpawn : ItemsToSpawn->GetItemsToSpawn())
	{
		for(int32 i = 0; i < ItemToSpawn.QuantityToSpawn; i++)
		{
			FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->GetActorLocation(), SpawnVolume->GetActorScale3D() * 50.0f);
			AItem* Item = World->SpawnActor<AItem>(Location, UKismetMathLibrary::RandomRotator(true));
			Item->Init(ItemToSpawn.ItemData->GetItem());
		}
	}
}

