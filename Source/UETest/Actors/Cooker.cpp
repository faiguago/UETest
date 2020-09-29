// Fill out your copyright notice in the Description page of Project Settings.


#include "Cooker.h"
#include "Item.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACooker::ACooker()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ButtonToCook = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonToCook"));
	ButtonToCook->SetupAttachment(Root);

	LocationToSpawnNewItem = CreateDefaultSubobject<UArrowComponent>(TEXT("LocationToSpawnNewItem"));
	LocationToSpawnNewItem->SetupAttachment(Root);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ACooker::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap events
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACooker::OnBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ACooker::OnEndOverlap);

	// Create dynamic material for button
	DynamicButtonMaterial = ButtonToCook->CreateAndSetMaterialInstanceDynamic(0);
	UpdateButtonState();
}

// Called every frame
void ACooker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACooker::Cook()
{
	if (!bCanCook)
		return;

	bIsCooking = true;

	UItemDataAsset* ItemDataAssetToCook = nullptr;
	for (const auto& Recipe : RecipesDataAsset->GetRecipes())
	{
		ItemDataAssetToCook = AnalizeRecipe(Recipe);
		if (ItemDataAssetToCook)
		{
			SpawnItem(ItemDataAssetToCook);
			break;
		}
	}

	bIsCooking = false;
	UpdateButtonState();
}

void ACooker::SpawnItem(UItemDataAsset* ItemDataAssetToCook)
{
	UWorld* const World = GetWorld();
	if (World)
	{
		AItem* Item = World->SpawnActor<AItem>(LocationToSpawnNewItem->GetComponentLocation(), UKismetMathLibrary::RandomRotator(true));
		Item->Init(ItemDataAssetToCook->GetItem());
	}

	for (int32 i = 0; i < ItemsToCook.Num(); i++)
	{
		ItemsToCook[i]->Destroy();
	}

	ItemsType.Empty();
	ItemsToCook.Empty();
}

UItemDataAsset* ACooker::AnalizeRecipe(const FRecipeData& Recipe)
{
	bool bCookThisRecipe = true;

	const auto& ItemsFromRecipe = Recipe.GetRecipe();
	for (int32 i = 0; i < ItemsFromRecipe.Num(); i++)
	{
		if (!ItemsType.IsValidIndex(i) || !ItemsFromRecipe.Contains(ItemsType[i]))
		{
			bCookThisRecipe = false;
			break;
		}
	}

	if (bCookThisRecipe)
	{
		int32 Index = FMath::RandHelper(Recipe.GetProbableResults().Num());
		return Recipe.GetProbableResults()[Index];
	}
	else
	{
		return nullptr;
	}
}

void ACooker::OnBeginOverlap(UPrimitiveComponent* InOverlappedComponent, AActor* InOtherActor, UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex, bool InbFromSweep, const FHitResult& InSweepResult)
{
	AItem* Item = Cast<AItem>(InOtherActor);
	if (!Item)
		return;

	ItemsToCook.Add(Item);
	ItemsType.Add(Item->GetItemType());

	UpdateButtonState();
}

void ACooker::OnEndOverlap(UPrimitiveComponent* InOverlappedComponent, AActor* InOtherActor, UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex)
{
	if (bIsCooking)
		return;

	AItem* Item = Cast<AItem>(InOtherActor);
	if (!Item)
		return;

	if (ItemsToCook.Contains(Item))
	{
		ItemsToCook.Remove(Item);
		ItemsType.Remove(Item->GetItemType());
	}

	UpdateButtonState();
}

void ACooker::UpdateButtonState()
{
	if (ItemsToCook.Num() >= MinItemsToActivateCooker)
	{
		bCanCook = true;
		DynamicButtonMaterial->SetVectorParameterValue(TEXT("Albedo"), FLinearColor::Red);
	}
	else
	{
		bCanCook = false;
		DynamicButtonMaterial->SetVectorParameterValue(TEXT("Albedo"), FLinearColor::White);
	}
}
