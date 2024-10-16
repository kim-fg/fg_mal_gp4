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
	UPROPERTY(EditAnywhere)
	float MusicVolume;

	UPROPERTY(EditAnywhere)
	float SFXVolume;

	UFUNCTION()
	void GetMusicVolume();

	UFUNCTION()
	void GetSFXVolume();

	
};
