#include "MoodInputModifierLookSensitivity.h"
#include "MoodEnhancedInputUserSettings.h"
#include "EnhancedPlayerInput.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "Subsystems/WorldSubsystem.h"
#include "EnhancedInputSubsystems.h"

FInputActionValue UMoodInputModifierLookSensitivity::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
	if (!Settings)
	{
		Settings = PlayerInput->GetOwningLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->GetUserSettings<UMoodEnhancedInputUserSettings>();
	}
	return CurrentValue.Get<FVector>() * Settings->GetAimSensVector();
}
