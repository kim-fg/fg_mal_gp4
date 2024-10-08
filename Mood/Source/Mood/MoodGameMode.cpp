// Copyright Epic Games, Inc. All Rights Reserved.

#include "MoodGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMoodGameMode::AMoodGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void AMoodGameMode::GameFinished()
{
	GameFinishedSig.Broadcast();
}


void AMoodGameMode::Respawn()
{
	PlayerRespawn.Broadcast();
}

