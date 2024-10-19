#include "MoodGameInstance.h"
#include "MoodUserSettings.h"
#include "Sound/SoundClass.h"

void UMoodGameInstance::Init()
{
	Super::Init();
	
	UserSettings = Cast<UMoodUserSettings>(GEngine->GetGameUserSettings());

	SetDefaultUserSettings();
}

void UMoodGameInstance::SetDefaultUserSettings()
{
	if (!UserSettings->GetSettingsExists())
	{
		UserSettings->SetMusicVolume(1.f);
		UserSettings->SetSFXVolume(1.f);



		UserSettings->SetSettingsExists(true);
	}
	else
	{
		MusicSoundClass->Properties.Volume = UserSettings->GetMusicVolume();
		SFXSoundClass->Properties.Volume = UserSettings->GetSFXVolume();

	}
}
