// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemHandleComponent.generated.h"

class UCameraComponent;
class AItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UETEST_API UItemHandleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemHandleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init(UCameraComponent* InCurrentCamera, USceneComponent* InItemLocation);

	void GrabItem();

	void UngrabItem();

private:

	UPROPERTY()
	UCameraComponent* CurrentCamera;

	UPROPERTY()
	AItem* CurrentItem;

	UPROPERTY()
	USceneComponent* ItemLocation;

	bool bIsGrabbingItem;

	bool bWasAttached;

	float Timer = 0.0f;
};
