// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemHandleComponent.h"
#include "../UETestCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "../Actors/Item.h"

// Sets default values for this component's properties
UItemHandleComponent::UItemHandleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemHandleComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UItemHandleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CurrentCamera || !ItemLocation)
		return;

	if (bWasAttached)
		return;

	if (bIsGrabbingItem)
	{
		Timer += DeltaTime;
		Timer = FMath::Clamp(Timer, 0.0f, 1.0f);
		if (Timer >= 1.0f)
		{
			bWasAttached = true;
			FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
			CurrentItem->AttachToComponent(ItemLocation, Rules);
		}
		else
		{
			CurrentItem->SetActorLocation(FMath::Lerp(CurrentItem->GetActorLocation(), ItemLocation->GetComponentLocation(), Timer));
		}
	}
	else
	{
		FHitResult OutHit;
		FVector Start = CurrentCamera->GetComponentLocation();
		if (UKismetSystemLibrary::LineTraceSingle(this, Start, Start + CurrentCamera->GetForwardVector() * 10000.0f, ETraceTypeQuery::TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::None, OutHit, true))
		{
			AItem* Item = Cast<AItem>(OutHit.Actor);
			if (Item)
			{
				CurrentItem = Item;
				Item->UpdateFresnel(1.0f);
			}
			else if (CurrentItem)
			{
				CurrentItem->UpdateFresnel(0.0f);
				CurrentItem = nullptr;
			}
		}
	}
}

void UItemHandleComponent::Init(UCameraComponent* InCurrentCamera, USceneComponent* InItemLocation)
{
	if (!InCurrentCamera || !InItemLocation)
		return;

	ItemLocation = InItemLocation;
	CurrentCamera = InCurrentCamera;
}

void UItemHandleComponent::GrabItem()
{
	if (!CurrentItem || !CurrentItem->GetIsGrabbable())
		return;

	Timer = 0.0f;
	bWasAttached = false;
	bIsGrabbingItem = true;

	CurrentItem->UpdatePhysicsState(false);
}

void UItemHandleComponent::UngrabItem()
{
	if (!CurrentItem)
		return;

	bIsGrabbingItem = false;
	if (bWasAttached)
	{
		bWasAttached = false;
		FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, false);
		CurrentItem->DetachFromActor(Rules);
	}

	CurrentItem->UpdatePhysicsState(true);
}