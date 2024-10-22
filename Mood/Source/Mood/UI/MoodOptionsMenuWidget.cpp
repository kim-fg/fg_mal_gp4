#include "MoodOptionsMenuWidget.h"
#include "MoodCyberButton.h"
#include "Components/Slider.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Components/TextBlock.h"
#include "../MoodEnhancedInputUserSettings.h"
#include "EnhancedInputSubsystems.h"
#include "CoreMinimal.h"
#include "MoodGameInstance.h"
#include "MoodUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"

void UMoodOptionsMenuWidget::ApplySettings_Implementation()
{
	Settings->SetAimSensitivity(MouseSensitivitySlider->GetValue(), MouseSensitivitySlider->GetValue());
	MouseSensitivitySavedValue = Settings->GetAimSensVector().X;
	
	MusicSoundClass->Properties.Volume = MusicVolumeSlider->GetValue();
	SFXSoundClass->Properties.Volume = SFXVolumeSlider->GetValue();
	
	UserSettings->SetMusicVolume(MusicVolumeSlider->GetValue());
	UserSettings->SetSFXVolume(SFXVolumeSlider->GetValue());
	
}
void UMoodOptionsMenuWidget::OpenWidget_Implementation()
{
	this->SetVisibility(ESlateVisibility::HitTestInvisible);
	//MasterVolumeSlider->SetValue(MasterVolumeSavedValue);
	MusicVolumeSlider->SetValue(UserSettings->GetMusicVolume());
	SFXVolumeSlider->SetValue(UserSettings->GetSFXVolume());
	MouseSensitivitySlider->SetValue(MouseSensitivitySavedValue);
	BrightnessSlider->SetValue(BrightnessSavedValue);
}
void UMoodOptionsMenuWidget::CloseWidget_Implementation()
{
	//this->SetVisibility(ESlateVisibility::HitTestInvisible);
}
void UMoodOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameInstance = Cast<UMoodGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ApplySettingsButton->ButtonClickedSig.AddUniqueDynamic(this, &UMoodOptionsMenuWidget::ApplySettings);
	CloseOptionsMenu->ButtonClickedSig.AddUniqueDynamic(this, &UMoodOptionsMenuWidget::CloseWidget);
	if (!Settings)
		Settings = GetOwningLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->GetUserSettings<UMoodEnhancedInputUserSettings>();
	MouseSensitivitySavedValue = Settings->GetAimSensVector().X;
	this->SetVisibility(ESlateVisibility::Hidden);
	UserSettings = Cast<UMoodUserSettings>(GEngine->GetGameUserSettings());
}

void UMoodOptionsMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//MasterVolumeSliderValue->SetText(FText::FromString(FString::SanitizeFloat(MasterVolumeSlider->GetValue(), 1)));
	MusicVolumeSliderValue->SetText(FText::FromString(FString::SanitizeFloat(MusicVolumeSlider->GetValue(), 1)));
	SFXVolumeSliderValue->SetText(FText::FromString(FString::SanitizeFloat(SFXVolumeSlider->GetValue(), 1)));
	MouseSensitivitySliderValue->SetText(FText::FromString(FString::SanitizeFloat(MouseSensitivitySlider->GetValue(), 1)));
	BrightnessSliderValue->SetText(FText::FromString(FString::SanitizeFloat(BrightnessSlider->GetValue(), 1)));
}
