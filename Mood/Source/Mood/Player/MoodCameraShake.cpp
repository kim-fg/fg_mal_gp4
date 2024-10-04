// Fill out your copyright notice in the Description page of Project Settings.


#include "MoodCameraShake.h"

UMoodGunCameraShake::UMoodGunCameraShake()
{
	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.5f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(0.5f, 1.5f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(0.5f, 1.5f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(0.5f, 1.5f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(0.5f, 1.5f);

	FOVOscillation.Amplitude = FMath::RandRange(0.f, 0.5f);
}

UMoodShotgunCameraShake::UMoodShotgunCameraShake()
{
	OscillationDuration = 0.35f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.5f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(2.f, 3.f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(0.0f, 1.f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(2.f, 3.f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(0.0f, 1.0f);

	FOVOscillation.Amplitude = FMath::RandRange(1.5f, 3.5f);
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
	OscillationDuration = 0.2f;
	OscillationBlendInTime = 0.5f;
	OscillationBlendOutTime = 0.5f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(0.7f, 1.5f);
	RotOscillation.Pitch.Frequency = 15.f;

	RotOscillation.Yaw.Amplitude = FMath::RandRange(0.5f, 1.1f);
	RotOscillation.Yaw.Frequency = 9.0f;

	RotOscillation.Roll.Amplitude = FMath::RandRange(0.4f, 0.6f);
	RotOscillation.Roll.Frequency = 6.f;

	bSingleInstance = true;
}