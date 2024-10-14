#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodLostScreen.h"
#include "MoodPauseMenu.generated.h"

class UButton;
class UMoodCyberButton;
class UMoodOptionsMenuWidget;

UCLASS()
class UMoodPauseMenu : public UMoodLostScreen
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* OpenOptionsMenuButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* ResumeButton;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenOptionsMenu();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResumeGame();

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodOptionsMenuWidget* OptionsMenuWidget;

protected:
	virtual void NativeConstruct() override;
};