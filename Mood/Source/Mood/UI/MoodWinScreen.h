#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodWinScreen.generated.h"

class UButton;

UCLASS()
class UMoodWinScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidgetOptional))
	UButton* MainMenuButton;

	//Show stats for the player upon finish?

	UFUNCTION(Blueprintable, BlueprintCallable)
	void ReturnToMainMenu();

	UFUNCTION(BlueprintNativeEvent)
	void PlayFadeAnimation();

	virtual void NativeConstruct() override;

	UPROPERTY()
	class UMoodGameInstance* MoodGameInstance;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainMenu;
};