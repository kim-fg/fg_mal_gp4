#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodMainMenuWidget.generated.h"

class UMoodCyberButton;
class UMoodOptionsMenuWidget;
class UMoodLevelSelectWidget;
class UMoodGameInstance;
class UWidgetAnimation;
class UButton;

UCLASS()
class UMoodMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* StartGameButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* LevelSelectButton;
	
	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	UMoodCyberButton* OptionsButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* ExitGameButton;

	UPROPERTY(meta =(BindWidget), BlueprintReadWrite)
	UMoodLevelSelectWidget* LevelSelectWidget;

	UPROPERTY(meta =(BindWidget), BlueprintReadWrite)
	UMoodOptionsMenuWidget* OptionsMenuWidget;
	

	UPROPERTY()
	UMoodGameInstance* MoodGameInstance = nullptr;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintNativeEvent)
	void RequestFadeAnim();

	UFUNCTION(Blueprintable)
	void ShowLevelSelectMenu();

	UFUNCTION(Blueprintable)
	void ShowOptionsMenu();

	UFUNCTION(Blueprintable)
	void ExitGame();
};
