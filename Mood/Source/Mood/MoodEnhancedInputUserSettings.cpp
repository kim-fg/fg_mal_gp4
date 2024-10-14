#include "MoodEnhancedInputUserSettings.h"

void UMoodEnhancedInputUserSettings::SetAimSensitivity(float SensX, float SensY)
{
	AimSensX = SensX;
	AimSensY = SensY;
	ApplySettings();
}

FVector UMoodEnhancedInputUserSettings::GetAimSensVector() const
{
	return FVector(AimSensX, AimSensY, 1);
}
