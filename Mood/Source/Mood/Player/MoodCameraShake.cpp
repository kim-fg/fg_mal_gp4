// Fill out your copyright notice in the Description page of Project Settings.


#include "MoodCameraShake.h"

UMoodShootCameraShake::UMoodShootCameraShake()
{
	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.1f;
	OscillationBlendOutTime = 0.5f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(0.f, 1.f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(0.0f, 1.f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(0.f, 1.f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(0.f, 1.f);

	FOVOscillation.Amplitude = FMath::RandRange(0.f, 0.5f);
}

UMoodShotgunCameraShake::UMoodShotgunCameraShake()
{
	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.1f;
	OscillationBlendOutTime = 0.5f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(1.0f, 2.0f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(0.0f, 1.f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(1.0f, 2.0f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(0.0f, 1.0f);

	FOVOscillation.Amplitude = FMath::RandRange(1.f, 2.f);
}

UMoodIdleHeadBob::UMoodIdleHeadBob()
{
	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.5f;
	OscillationBlendOutTime = 0.5f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(0.0f, 0.5f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(0.0f, 5.f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(0.0f, 0.4f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(0.0f, 3.0f);

	RotOscillation.Roll.Amplitude = FMath::RandRange(0.f, 0.2f);
	RotOscillation.Roll.Frequency = FMath::RandRange(0.f, 1.f);

	bSingleInstance = true;
}

UMoodWalkHeadBob::UMoodWalkHeadBob()
{
	OscillationDuration = 0.2f;
	OscillationBlendInTime = 0.5f;
	OscillationBlendOutTime = 0.5f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(0.2f, 0.8f);
	RotOscillation.Pitch.Frequency = 15.f;

	RotOscillation.Yaw.Amplitude = FMath::RandRange(0.2f, 0.6f);
	RotOscillation.Yaw.Frequency = 9.0f;

	RotOscillation.Roll.Amplitude = FMath::RandRange(0.2f, 0.4f);
	RotOscillation.Roll.Frequency = 6.f;

	bSingleInstance = true;
}

UMoodSprintHeadBob::UMoodSprintHeadBob()
{
	OscillationDuration = 0.15f;
	OscillationBlendInTime = 0.1f;
	OscillationBlendOutTime = 0.2f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(0.2f, 0.8f);
	RotOscillation.Pitch.Frequency = 40.f;

	RotOscillation.Yaw.Amplitude = FMath::RandRange(0.2f, 0.6f);
	RotOscillation.Yaw.Frequency = 24.0f;

	RotOscillation.Roll.Amplitude = FMath::RandRange(0.2f, 0.4f);
	RotOscillation.Roll.Frequency = 16.f;

	bSingleInstance = true;
}