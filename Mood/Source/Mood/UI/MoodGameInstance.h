#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MoodGameInstance.generated.h"

class UMoodUserSettings;

UCLASS()
class UMoodGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	//Reference to levels
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> MainMenu;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level1;
    	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level2;

	

	UPROPERTY()
	UMoodUserSettings* UserSettings;
	
	UPROPERTY(BlueprintReadOnly)
	float MusicVolume;

	UPROPERTY(BlueprintReadOnly)
	float SFXVolume;

	UPROPERTY(BlueprintReadOnly)
	float MouseSensitivity;

protected:

	virtual void Init() override;
	
};