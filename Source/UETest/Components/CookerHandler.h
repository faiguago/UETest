// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CookerHandler.generated.h"

class UCameraComponent;
class ACooker;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UETEST_API UCookerHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCookerHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init(UCameraComponent* InCurrentCamera);

	void Cook();

private:

	UPROPERTY()
	UCameraComponent* CurrentCamera;

	UPROPERTY()
	ACooker* CurrentCooker;
};
