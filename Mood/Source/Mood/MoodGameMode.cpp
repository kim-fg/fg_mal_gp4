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

void AMoodGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMoodGameMode::GameFinished()
{
	GameFinishedSig.Broadcast();
}

void AMoodGameMode::Respawn()
{
	PlayerRespawn.Broadcast();
}

void AMoodGameMode::ChangeMoodValue(int Value)
{
	MoodMeterValue += Value;
	MoodMeterValue = FMath::Clamp(MoodMeterValue, 0, 1000);
	
	UE_LOG(LogTemp, Log, TEXT("Add %i - New Value: %i"), Value, MoodMeterValue);
}