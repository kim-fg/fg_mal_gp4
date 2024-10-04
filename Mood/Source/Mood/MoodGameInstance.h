#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MoodGameInstance.generated.h"

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
};