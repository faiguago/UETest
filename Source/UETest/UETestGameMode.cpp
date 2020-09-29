// Copyright Epic Games, Inc. All Rights Reserved.

#include "UETestGameMode.h"
#include "UETestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUETestGameMode::AUETestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
