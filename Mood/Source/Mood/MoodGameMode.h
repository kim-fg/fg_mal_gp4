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
};



