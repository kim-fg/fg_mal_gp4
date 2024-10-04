#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodLostScreen.generated.h"

class UButton;

UCLASS()
class UMoodLostScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	UFUNCTION(Blueprintable)
	void RestartLevel();

	UFUNCTION(Blueprintable)
	void ToMainMenu();

	virtual void NativeConstruct() override;

	UPROPERTY()
	class UMoodGameInstance* MoodGameInstance;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainMenu;
};