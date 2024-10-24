#pragma once

#include "CoreMinimal.h"
#include "MoodLostScreen.h"
#include "MoodPauseMenu.generated.h"

class UMoodHealthComponent;
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

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* ResetLevelButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* KillPlayerButton;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenOptionsMenu();

	virtual void RestartLevel() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResumeGame();

	UFUNCTION()
	void FullResetLevel();

	UFUNCTION()
	void PassHealthComponent(UMoodHealthComponent* PassHealthComp);

	UFUNCTION()
	void KillPlayerInPause();

	UPROPERTY()
	UMoodHealthComponent* PlayerHealth;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodOptionsMenuWidget* OptionsMenuWidget;

protected:
	virtual void NativeConstruct() override;

private:

};