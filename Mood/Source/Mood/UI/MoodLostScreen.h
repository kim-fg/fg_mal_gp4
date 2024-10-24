#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodLostScreen.generated.h"

class UButton;
class UMoodCyberButton;

UCLASS()
class UMoodLostScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetOptional))
	UMoodCyberButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	UMoodCyberButton* MainMenuButton;

	UFUNCTION(Blueprintable)
	virtual void RestartLevel();

	UFUNCTION(Blueprintable)
	void ToMainMenu();

	UFUNCTION(BlueprintNativeEvent)
	void RequestBleedoutAnimation();

	UFUNCTION(BlueprintCallable)
	void DisplayMenu();

	virtual void NativeConstruct() override;

	UPROPERTY()
	class UMoodGameInstance* MoodGameInstance;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainMenu;


	UPROPERTY()
	class AMoodGameMode* GameMode;
	
};