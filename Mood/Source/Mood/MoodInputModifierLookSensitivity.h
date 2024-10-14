#pragma once

#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "MoodInputModifierLookSensitivity.generated.h"

class UMoodEnhancedInputUserSettings;

UCLASS()
class UMoodInputModifierLookSensitivity : public UInputModifier
{
	GENERATED_BODY()

protected:
	virtual FInputActionValue ModifyRaw_Implementation(
		const UEnhancedPlayerInput* PlayerInput,
		FInputActionValue CurrentValue,
		float DeltaTime) override;

	UPROPERTY(Transient)
	UMoodEnhancedInputUserSettings* Settings;
};