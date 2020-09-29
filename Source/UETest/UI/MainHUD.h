// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class UETEST_API AMainHUD : public AHUD
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CrosshairWidgetTemplate;

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	UUserWidget* CrosshairWidget;
};
