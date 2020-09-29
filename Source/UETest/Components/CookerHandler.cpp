// Fill out your copyright notice in the Description page of Project Settings.


#include "CookerHandler.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Actors/Cooker.h"

// Sets default values for this component's properties
UCookerHandler::UCookerHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCookerHandler::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UCookerHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CurrentCamera)
		return;

	FHitResult OutHit;
	FVector Start = CurrentCamera->GetComponentLocation();
	if (UKismetSystemLibrary::LineTraceSingle(this, Start, Start + CurrentCamera->GetForwardVector() * 10000.0f, ETraceTypeQuery::TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::None, OutHit, true))
	{
		ACooker* Cooker = Cast<ACooker>(OutHit.Actor);
		if (Cooker && OutHit.GetComponent()->GetName().Equals(TEXT("ButtonToCook")))
		{
			CurrentCooker = Cooker;
		}
		else
		{
			CurrentCooker = nullptr;
		}
	}
}

void UCookerHandler::Init(UCameraComponent* InCurrentCamera)
{
	if (!InCurrentCamera)
		return;

	CurrentCamera = InCurrentCamera;
}

void UCookerHandler::Cook()
{
	if (CurrentCooker)
	{
		CurrentCooker->Cook();
	}
}