#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodOptionsMenuWidget.generated.h"

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
	
protected:
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* ApplySettingsButton;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ApplySettings();

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* CloseOptionsMenu;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* MasterVolumeSliderValue;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	USlider* MasterVolumeSlider;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* MusicVolumeSliderValue;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	USlider* MusicVolumeSlider;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* SFXVolumeSliderValue;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	USlider* SFXVolumeSlider;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* MouseSensitivitySliderValue;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	USlider* MouseSensitivitySlider;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* BrightnessSliderValue;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	USlider* BrightnessSlider;

	UPROPERTY()
	UMoodEnhancedInputUserSettings* Settings;

private:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
