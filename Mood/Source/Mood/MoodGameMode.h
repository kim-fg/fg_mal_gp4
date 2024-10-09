// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MoodGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerRespawn);

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

	int GetMoodMeterValue() { return MoodMeterValue; }

	void IncreaseMood(int Value);

	void DecreaseMood(int Value);

private:
	int MoodMeterValue = 0.f;
};



