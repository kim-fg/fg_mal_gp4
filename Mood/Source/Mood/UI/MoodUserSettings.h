#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "MoodUserSettings.generated.h"

class USoundClass;

UCLASS()
class UMoodUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:


	UFUNCTION()
	float GetMusicVolume();
	UFUNCTION()
	void SetMusicVolume(float NewVolume);

	UFUNCTION()
	float GetSFXVolume();
	UFUNCTION()
	void SetSFXVolume(float NewVolume);

	UFUNCTION()
	bool GetSettingsExists();
	UFUNCTION()
	void SetSettingsExists(bool bExists);

private:
	UPROPERTY(EditAnywhere)
	float MusicVolume;

	UPROPERTY(EditAnywhere)
	float SFXVolume;

	UPROPERTY()
	bool bSettingsExists = false;
	
};
