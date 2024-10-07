// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MoodGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameFinished);

UCLASS(minimalapi)
class AMoodGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMoodGameMode();

	UFUNCTION(BlueprintCallable)
	void GameFinished();

	UPROPERTY()
	FGameFinished GameFinishedSig;
};



