// Copyright Epic Games, Inc. All Rights Reserved.

#include "InfiniteProjectilesGameMode.h"
#include "InfiniteProjectilesCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInfiniteProjectilesGameMode::AInfiniteProjectilesGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
