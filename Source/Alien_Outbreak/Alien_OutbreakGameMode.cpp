// Copyright Epic Games, Inc. All Rights Reserved.

#include "Alien_OutbreakGameMode.h"
#include "Alien_OutbreakCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAlien_OutbreakGameMode::AAlien_OutbreakGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
