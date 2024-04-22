// Copyright Epic Games, Inc. All Rights Reserved.

#include "ToyGameMode.h"
#include "ToyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AToyGameMode::AToyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
