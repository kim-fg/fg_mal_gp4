// Copyright Epic Games, Inc. All Rights Reserved.

#include "MoodGameMode.h"

#include "Kismet/GameplayStatics.h"
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
	SetSlowMotion();
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
	{
		if (bIsChangingMood)
			return;
		Value *= MoodLossWhenHit;
	}
	
	MoodMeterValue += Value * MoodGainWhenDamaging;
	MoodMeterValue = FMath::Clamp(MoodMeterValue, 0, 1000);

	auto NewMoodState = GetMoodState();
	if (NewMoodState != previousMoodState) {
		OnMoodChanged.Broadcast(NewMoodState);
		CheckSlowMotionValidity(previousMoodState, NewMoodState);
	}
}

void AMoodGameMode::ResetMoodValue() {
	MoodMeterValue = 0;
}

void AMoodGameMode::ResetDamageTime() {
	TimeSinceEnemyDamaged = 0;
}

void AMoodGameMode::DecreaseMoodOverTime() {
	if (bIsChangingMood)
		return;
	
	auto PreviousMoodState = GetMoodState();
	
	TimeSinceEnemyDamaged += GetWorld()->DeltaTimeSeconds;

	if (TimeSinceEnemyDamaged >= TimeIdleBeforeMoodLoss)
		MoodMeterValue -= GetWorld()->DeltaTimeSeconds * MoodDecayRate;

	MoodMeterValue = FMath::Clamp(MoodMeterValue, 0, 1000);

	auto NewMoodState = GetMoodState();
	if (PreviousMoodState != NewMoodState) {
		OnMoodChanged.Broadcast(NewMoodState);
		CheckSlowMotionValidity(PreviousMoodState, NewMoodState);
	}
}

void AMoodGameMode::CheckSlowMotionValidity(EMoodState PreviousState, EMoodState NewMoodState)
{
	switch (NewMoodState)
	{
	case Ems_Mood666:
		if (TimeLeftMood666 <= 0.f)
		{
			bIsChangingMood = true;
			TimeLeftMood666 = TimerSlowMotionReset;
			OnSlowMotionTriggered.Broadcast(NewMoodState);
		}
		break;
	case Ems_Mood444:
		if (PreviousState > NewMoodState && TimeLeftMood444 <= 0.f)
		{
			bIsChangingMood = true;
			TimeLeftMood444 = TimerSlowMotionReset;
			OnSlowMotionTriggered.Broadcast(NewMoodState);
		}
		break;
	case Ems_Mood222:
		if (PreviousState > NewMoodState && TimeLeftMood222 <= 0.f)
		{
			bIsChangingMood = true;
			TimeLeftMood222 = TimerSlowMotionReset;
			OnSlowMotionTriggered.Broadcast(NewMoodState);
		}
		TimeLeftMood666 = 0.f;
		break;
	case Ems_NoMood:
		TimeLeftMood666 = 0.f;
		TimeLeftMood444 = 0.f;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("MoodGameMode: No new mood state"));
	}
}

void AMoodGameMode::SetSlowMotion()
{
	const auto DeltaTime = GetWorld()->DeltaTimeSeconds;
	if (TimeLeftMood222 >= 0.f)
		TimeLeftMood222 -= DeltaTime;
	if (TimeLeftMood444 >= 0.f)
		TimeLeftMood444 -= DeltaTime;
	if (TimeLeftMood666 >= 0.f)
		TimeLeftMood666 -= DeltaTime;

	if (!bIsChangingMood)
		return;
	
	if (!bHasReachedTimeDilationBottom)
	{
		CurrentTimeDilation = FMath::Lerp(CurrentTimeDilation, MoodChangeTimeDilation, MoodChangeAlpha);
		if (CurrentTimeDilation <= MoodChangeTimeDilation + 0.05f)
			bHasReachedTimeDilationBottom = true;
	}
	else
	{
		CurrentTimeDilation = FMath::Lerp(CurrentTimeDilation, 1.1f, MoodChangeAlpha);
		if (CurrentTimeDilation >= 1.f)
		{
			CurrentTimeDilation = 1.f;
			bHasReachedTimeDilationBottom = false;
			bIsChangingMood = false;
		}
	}

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), CurrentTimeDilation);
}
