#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MoodGameInstance.generated.h"

class UMoodUserSettings;
class UMusicSoundClass;

UCLASS()
class UMoodGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	//Reference to levels
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> MainMenu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> Level1;
    	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> Level2;

	UPROPERTY()
	UMoodUserSettings* UserSettings;

	UPROPERTY(EditDefaultsOnly)
	USoundClass* MusicSoundClass;
	UPROPERTY(EditDefaultsOnly)
	USoundClass* SFXSoundClass;


protected:

	virtual void Init() override;

	void SetDefaultUserSettings();
	
};