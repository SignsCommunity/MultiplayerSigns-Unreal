// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MultiplayerTopDownGameMode.h"
#include "MultiplayerTopDownPlayerController.h"
#include "MultiplayerTopDownCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayerTopDownGameMode::AMultiplayerTopDownGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMultiplayerTopDownPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}