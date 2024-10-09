#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodMainMenuWidget.generated.h"

class UMoodOptionsMenuWidget;
class UMoodLevelSelectWidget;
class UMoodGameInstance;
class UButton;

UCLASS()
class UMoodMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	UButton* LevelSelectButton;
	
	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UButton* ExitGameButton;

	UPROPERTY(meta =(BindWidget))
	UMoodLevelSelectWidget* LevelSelectWidget;

	UPROPERTY(meta =(BindWidget))
	UMoodOptionsMenuWidget* OptionsMenuWidget;
	

	UPROPERTY()
	UMoodGameInstance* MoodGameInstance = nullptr;

	virtual void NativeConstruct() override;

	UFUNCTION(Blueprintable)
	void StartGame();

	UFUNCTION(Blueprintable)
	void ShowLevelSelectMenu();

	UFUNCTION(Blueprintable)
	void ShowOptionsMenu();

	UFUNCTION(Blueprintable)
	void ExitGame();
};
