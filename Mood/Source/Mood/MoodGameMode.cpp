// Copyright Epic Games, Inc. All Rights Reserved.

#include "MoodGameMode.h"

#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

AMoodGameMode::AMoodGameMode()
	: Super() {
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PrimaryActorTick.bCanEverTick = true;
}

void AMoodGameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	DecreaseMoodOverTime();
}

void AMoodGameMode::GameFinished() {
	GameFinishedSig.Broadcast();
}

void AMoodGameMode::Respawn() {
	PlayerRespawn.Broadcast();
	ResetMoodValue();
}

EMoodState AMoodGameMode::GetMoodState() const {
	if (MoodMeterValue >= 666) { return Ems_Mood666; }
	if (MoodMeterValue >= 444) { return Ems_Mood444; }
	if (MoodMeterValue >= 222) { return Ems_Mood222; }
	return Ems_NoMood;
}

float AMoodGameMode::GetGibbingChance() {
	auto T = 0.0f;
	switch (GetMoodState()) {
	case Ems_Mood666:
		T = 1.0f;
		break;
	case Ems_Mood444:
		T = 0.66f;
		break;
	case Ems_Mood222:
		T = 0.33f;
		break;
	case Ems_NoMood:
		T = 0.0f;
		break;
	}

	return UKismetMathLibrary::Lerp(MinGibbingChance, MaxGibbingChance, T);
}

void AMoodGameMode::ChangeMoodValue(int Value) {
	auto previousMoodState = GetMoodState();

	if (Value < 0)
		Value /= 2;

	MoodMeterValue += Value * 5;
	MoodMeterValue = FMath::Clamp(MoodMeterValue, 0, 1000);

	auto NewMoodState = GetMoodState();
	if (NewMoodState != previousMoodState) {
		OnMoodChanged.Broadcast(NewMoodState);
	}
}

void AMoodGameMode::ResetMoodValue() {
	MoodMeterValue = 0;
}

void AMoodGameMode::ResetDamageTime() {
	TimeSinceEnemyDamaged = 0;
}

void AMoodGameMode::DecreaseMoodOverTime() {
	auto PreviousMoodState = GetMoodState();
	
	TimeSinceEnemyDamaged += GetWorld()->DeltaTimeSeconds;

	if (TimeSinceEnemyDamaged >= 1)
		MoodMeterValue -= GetWorld()->DeltaTimeSeconds;

	MoodMeterValue = FMath::Clamp(MoodMeterValue, 0, 1000);

	auto NewMoodState = GetMoodState();
	if (PreviousMoodState != NewMoodState) {
		OnMoodChanged.Broadcast(NewMoodState);
	}
}
