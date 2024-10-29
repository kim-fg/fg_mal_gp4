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
	TimeSinceSlowMotion();
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

	if ((MoodMeterValue + Value) > MoodMeterValue)
	{
		OnEnemyHit.Broadcast();
	}

	if (Value < 0)
	{
		if (bIsChangingMood || !bCanLoseMood)
			return;
		Value *= MoodLossWhenHit;
	}
	
	MoodMeterValue += Value * MoodGainWhenDamaging;
	MoodMeterValue = FMath::Clamp(MoodMeterValue, 0, 1000);
	
	auto NewMoodState = GetMoodState();
	if (NewMoodState != previousMoodState) {
		OnMoodChanged.Broadcast(NewMoodState);
		CheckSlowMotionValidity(previousMoodState, NewMoodState);
		if (NewMoodState < previousMoodState)
		{
			bCanLoseMood = false;
			GetWorldTimerManager().SetTimer(KeepMoodTimer, this, &AMoodGameMode::AllowMoodDecrease, TimeToKeepMood, false, TimeToKeepMood);
		}
	}
}

void AMoodGameMode::ResetMoodValue() {
	MoodMeterValue = 0;
}

void AMoodGameMode::ResetDamageTime() {
	TimeSinceEnemyDamaged = 0;
}

void AMoodGameMode::AllowMoodDecrease()
{
	bCanLoseMood = true;
}

void AMoodGameMode::DecreaseMoodOverTime() {
	if (bIsChangingMood)
		return;
	
	auto PreviousMoodState = GetMoodState();
	
	TimeSinceEnemyDamaged += GetWorld()->DeltaTimeSeconds;

	if (TimeSinceEnemyDamaged >= TimeIdleBeforeMoodLoss)
	{
		switch (PreviousMoodState)
		{
		case Ems_NoMood:
			MoodDecayRate = MoodDecayRate0;
			break;
		case Ems_Mood222:
			MoodDecayRate = MoodDecayRate222;
			break;
		case Ems_Mood444:
			MoodDecayRate = MoodDecayRate444;
			break;
		case Ems_Mood666:
			MoodDecayRate = MoodDecayRate666;
			break;
			default:
				UE_LOG(LogTemp, Error, TEXT("AMoodGameMode::DecreaseMoodOverTime"))
		}
		MoodMeterValue -= GetWorld()->DeltaTimeSeconds * MoodDecayRate;
	}

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
			TriggerSlowMotion(NewMoodState);
			TimeLeftMood666 = TimerSlowMotionReset;
		}
		break;
	case Ems_Mood444:
		if (PreviousState > NewMoodState && TimeLeftMood444 <= 0.f)
		{
			TriggerSlowMotion(NewMoodState);
			TimeLeftMood444 = TimerSlowMotionReset;
		}
		break;
	case Ems_Mood222:
		if (PreviousState > NewMoodState && TimeLeftMood222 <= 0.f)
		{
			TriggerSlowMotion(NewMoodState);
			TimeLeftMood222 = TimerSlowMotionReset;
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

void AMoodGameMode::TimeSinceSlowMotion()
{
	const auto DeltaTime = GetWorld()->DeltaTimeSeconds;
	if (TimeLeftMood222 >= 0.f)
		TimeLeftMood222 -= DeltaTime;
	if (TimeLeftMood444 >= 0.f)
		TimeLeftMood444 -= DeltaTime;
	if (TimeLeftMood666 >= 0.f)
		TimeLeftMood666 -= DeltaTime;
}

void AMoodGameMode::TriggerSlowMotion(EMoodState NewMoodState)
{
	if (bCanLoseMood)
		bCanLoseMood = false;

	bIsChangingMood = true;
	OnSlowMotionTriggered.Broadcast(NewMoodState);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), MoodChangeTimeDilation);
	GetWorldTimerManager().SetTimer(TimerSlowMotion, this, &AMoodGameMode::EndSlowMotion, SlowMotionTime, false, SlowMotionTime);
}

void AMoodGameMode::EndSlowMotion()
{
	bIsChangingMood = false;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
	OnSlowMotionEnded.Broadcast();
}