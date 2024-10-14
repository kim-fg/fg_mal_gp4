#include "MoodOptionsMenuWidget.h"
#include "MoodCyberButton.h"
#include "Components/Slider.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Input/SSlider.h"
#include "Styling/DefaultStyleCache.h"
#include "Styling/UMGCoreStyle.h"
#include "Components/TextBlock.h"
#include "../MoodEnhancedInputUserSettings.h"
#include "../MoodInputModifierLookSensitivity.h"
#include "EnhancedPlayerInput.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "CoreMinimal.h"
#include "InputModifiers.h"

void UMoodOptionsMenuWidget::ApplySettings_Implementation()
{
	Settings->SetAimSensitivity(MouseSensitivitySlider->Value, MouseSensitivitySlider->Value);
	MouseSensitivitySavedValue = Settings->GetAimSensVector().X;


}
void UMoodOptionsMenuWidget::OpenWidget_Implementation()
{
	this->SetVisibility(ESlateVisibility::HitTestInvisible);
	MasterVolumeSlider->SetValue(MasterVolumeSavedValue);
	MusicVolumeSlider->SetValue(MusicVolumeSavedValue);
	SFXVolumeSlider->SetValue(SFXVolumeSavedValue);
	MouseSensitivitySlider->SetValue(MouseSensitivitySavedValue);
	BrightnessSlider->SetValue(BrightnessSavedValue);
}
void UMoodOptionsMenuWidget::CloseWidget_Implementation()
{
	this->SetVisibility(ESlateVisibility::HitTestInvisible);
}
void UMoodOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ApplySettingsButton->ButtonClickedSig.AddUniqueDynamic(this, &UMoodOptionsMenuWidget::ApplySettings);
	CloseOptionsMenu->ButtonClickedSig.AddUniqueDynamic(this, &UMoodOptionsMenuWidget::CloseWidget);
	if (!Settings)
		Settings = GetOwningLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->GetUserSettings<UMoodEnhancedInputUserSettings>();
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UMoodOptionsMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	MasterVolumeSliderValue->SetText(FText::FromString(FString::SanitizeFloat(MasterVolumeSlider->Value, 1)));
	MusicVolumeSliderValue->SetText(FText::FromString(FString::SanitizeFloat(MusicVolumeSlider->Value, 1)));
	SFXVolumeSliderValue->SetText(FText::FromString(FString::SanitizeFloat(SFXVolumeSlider->Value, 1)));
	MouseSensitivitySliderValue->SetText(FText::FromString(FString::SanitizeFloat(MouseSensitivitySlider->Value, 1)));
	BrightnessSliderValue->SetText(FText::FromString(FString::SanitizeFloat(BrightnessSlider->Value, 1)));
}
