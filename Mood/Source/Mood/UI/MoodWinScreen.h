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
	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	//Show stats for the player upon finish?

	UFUNCTION(Blueprintable)
	void ReturnToMainMenu();

	virtual void NativeConstruct() override;

	UPROPERTY()
	class UMoodGameInstance* MoodGameInstance;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainMenu;
};