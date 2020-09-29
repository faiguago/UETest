// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComp->SetSimulatePhysics(true);
	RootComponent = StaticMeshComp;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::Init(const FItemData& InItemData)
{
	ItemType = InItemData.ItemType;
	bIsGrabbable = InItemData.bIsGrabbable;
	StaticMeshComp->SetStaticMesh(InItemData.StaticMesh);
	StaticMeshComp->SetWorldScale3D(InItemData.WorldScale);

	if (bIsGrabbable)
	{
		 DynamicMaterial = UMaterialInstanceDynamic::Create(InItemData.MaterialToSet, this);
		 DynamicMaterial->SetScalarParameterValue(TEXT("Fresnel Effect"), 0.0f);
		 DynamicMaterial->SetVectorParameterValue(TEXT("Fresnel Color"), FMath::VRand() * 150.0f);
		 StaticMeshComp->SetMaterial(0, DynamicMaterial);
	}
	else
	{
		StaticMeshComp->SetMaterial(0, InItemData.MaterialToSet);
	}
}

void AItem::UpdateFresnel(float InValue)
{
	if (!bIsGrabbable || !DynamicMaterial)
		return;

	DynamicMaterial->SetScalarParameterValue(TEXT("Fresnel Effect"), InValue);
}

void AItem::UpdatePhysicsState(bool InNewState)
{
	StaticMeshComp->SetSimulatePhysics(InNewState);
	if (InNewState)
	{
		StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
