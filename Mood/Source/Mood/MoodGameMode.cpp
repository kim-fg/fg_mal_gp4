// Copyright Epic Games, Inc. All Rights Reserved.

#include "MoodGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMoodGameMode::AMoodGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PrimaryActorTick.bCanEverTick = true;
}

void AMoodGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DecreaseMoodOverTime();
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
	if (Value < 0)
		Value /= 2;
	
	MoodMeterValue += Value * 5;
}

void AMoodGameMode::ResetDamageTime()
{
	TimeSinceEnemyDamaged = 0;
}

void AMoodGameMode::DecreaseMoodOverTime()
{
	TimeSinceEnemyDamaged += GetWorld()->DeltaTimeSeconds;

	if (TimeSinceEnemyDamaged >= 1)
		MoodMeterValue -= GetWorld()->DeltaTimeSeconds;

	MoodMeterValue = FMath::Clamp(MoodMeterValue, 0, 1000);
}
