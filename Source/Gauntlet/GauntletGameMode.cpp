// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Gauntlet.h"
#include "GauntletGameMode.h"
#include "GauntletCharacter.h"

AGauntletGameMode::AGauntletGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
