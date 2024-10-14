#pragma once

#include "CoreMinimal.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "MoodEnhancedInputUserSettings.generated.h"


UCLASS()
class UMoodEnhancedInputUserSettings : public UEnhancedInputUserSettings
{
	GENERATED_BODY()

public:

	void SetAimSensitivity(float SensX, float SensY);

	FVector GetAimSensVector() const;

protected:
	UPROPERTY(EditAnywhere, Config)
	float AimSensX = 1;
	UPROPERTY(EditAnywhere, Config)
	float AimSensY = 1;
};