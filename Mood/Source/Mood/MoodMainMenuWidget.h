#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodMainMenuWidget.generated.h"

class UMoodGameInstance;
class UButton;

UCLASS()
class UMoodMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* LevelSelectButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;

	UPROPERTY()
	UMoodGameInstance* MoodGameInstance = nullptr;

	virtual void NativeConstruct() override;

	UFUNCTION(Blueprintable)
	void StartGame();

	UFUNCTION(Blueprintable)
	void LevelSelect();
};
