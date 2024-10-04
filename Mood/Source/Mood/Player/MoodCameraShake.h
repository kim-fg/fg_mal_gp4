// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shakes/LegacyCameraShake.h"
#include "MoodCameraShake.generated.h"

/**
 * 
 */
UCLASS()
class MOOD_API UMoodGunCameraShake : public ULegacyCameraShake
{
	GENERATED_BODY()

	UMoodGunCameraShake();
};

UCLASS()
class MOOD_API UMoodShotgunCameraShake : public ULegacyCameraShake
{
	GENERATED_BODY()

	UMoodShotgunCameraShake();
};

UCLASS()
class MOOD_API UMoodIdleHeadBob : public ULegacyCameraShake
{
	GENERATED_BODY()

	UMoodIdleHeadBob();
};

UCLASS()
class MOOD_API UMoodWalkHeadBob : public ULegacyCameraShake
{
	GENERATED_BODY()

	UMoodWalkHeadBob();
};

UCLASS()
class MOOD_API UMoodSprintHeadBob : public ULegacyCameraShake
{
	GENERATED_BODY()

	UMoodSprintHeadBob();
};

