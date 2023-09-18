// Copyright Epic Games, Inc. All Rights Reserved.

#include "CatGameMode.h"
#include "CatCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACatGameMode::ACatGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
