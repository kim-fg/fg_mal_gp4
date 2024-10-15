// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MoodGameMode.generated.h"

UENUM(BlueprintType)
enum EMoodState
{
	Ems_Mood666,
	Ems_Mood444,
	Ems_Mood222,
	Ems_NoMood
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerRespawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoodChanged, EMoodState, NewState);

UCLASS(minimalapi)
class AMoodGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void Tick(float DeltaTime) override;

public:
	AMoodGameMode();

	UFUNCTION(BlueprintCallable)
	void GameFinished();

	UFUNCTION(BlueprintCallable)
	void Respawn();
	
	UPROPERTY(BlueprintAssignable)
	FPlayerRespawn PlayerRespawn;

	UPROPERTY()
	FGameFinished GameFinishedSig;
	
	UPROPERTY(BlueprintAssignable)
	FOnMoodChanged OnMoodChanged;

	float GetMoodMeterValue() const { return MoodMeterValue; }
	EMoodState GetMoodState() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetGibbingChance();

	void ChangeMoodValue(int Value);
	void ResetMoodValue();
	void ResetDamageTime();

private:
	UPROPERTY(EditDefaultsOnly, Category=Gibbing)
	float MinGibbingChance = 0.1f;
	UPROPERTY(EditDefaultsOnly, Category=Gibbing)
	float MaxGibbingChance = 1.0f;
	
	float MoodMeterValue = 0.f;
	float TimeSinceEnemyDamaged = 0.f;

	// Slow motion
	UPROPERTY(EditDefaultsOnly)
	float TimerSlowMotionReset = 30.f;
	UPROPERTY(EditDefaultsOnly, Category=MoodMeter)
	float MoodChangeTimeDilation = 0.05f;
	UPROPERTY(EditDefaultsOnly, Category=MoodMeter)
	float MoodChangeAlpha = 0.01f;

	float TimeLeftMood666 = 0.f;
	float TimeLeftMood444 = 0.f;
	float TimeLeftMood222 = 0.f;
	bool bIsChangingMood = false;
	bool bHasReachedTimeDilationBottom = false;
	float CurrentTimeDilation = 1.f;

	void DecreaseMoodOverTime();

	void CheckSlowMotionValidity(EMoodState PreviousState, EMoodState NewMoodState);
	void SetSlowMotion();
};