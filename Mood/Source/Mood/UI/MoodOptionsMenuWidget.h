#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodOptionsMenuWidget.generated.h"

class UMoodGameInstance;
class UMoodUserSettings;
class UTextBlock;
class USlider;
class UMoodCyberButton;
class UMoodEnhancedInputUserSettings;

UCLASS()

class UMoodOptionsMenuWidget : public UUserWidget
{

	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenWidget();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CloseWidget();

	UPROPERTY()
	UMoodUserSettings* UserSettings;
	
protected:
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* ApplySettingsButton;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ApplySettings();

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* CloseOptionsMenu;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadWrite)
	UTextBlock* MasterVolumeSliderValue;
	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadWrite)
	USlider* MasterVolumeSlider;
	UPROPERTY()
	float MasterVolumeSavedValue = 1.f;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* MusicVolumeSliderValue;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	USlider* MusicVolumeSlider;
	UPROPERTY()
	float MusicVolumeSavedValue = 1.f;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* SFXVolumeSliderValue;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	USlider* SFXVolumeSlider;
	UPROPERTY()
	float SFXVolumeSavedValue = 1.f;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* MouseSensitivitySliderValue;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	USlider* MouseSensitivitySlider;
	UPROPERTY()
	float MouseSensitivitySavedValue = 1.f;

	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadWrite)
	UTextBlock* BrightnessSliderValue;
	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadWrite)
	USlider* BrightnessSlider;
	UPROPERTY()
	float BrightnessSavedValue = 0.5f;

	UPROPERTY()
	UMoodEnhancedInputUserSettings* Settings;



	UPROPERTY()
	UMoodGameInstance* GameInstance;

	UPROPERTY(EditDefaultsOnly)
	USoundClass* MusicSoundClass;

	UPROPERTY(EditDefaultsOnly)
	USoundClass* SFXSoundClass;

private:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
