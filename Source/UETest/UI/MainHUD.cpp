// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "Engine/World.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();
	if (!World)
		return;

	CrosshairWidget = CreateWidget<UUserWidget>(World, CrosshairWidgetTemplate);
	CrosshairWidget->AddToViewport();
}