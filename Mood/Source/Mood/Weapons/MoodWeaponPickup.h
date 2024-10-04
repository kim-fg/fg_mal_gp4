#pragma once

#include "MoodWeaponPickup.generated.h"

class UMoodPickUpComponent;
class UMoodWeaponComponent;

UCLASS(Abstract)
class AMoodWeaponPickup : public AActor {
	GENERATED_BODY()
public:
	AMoodWeaponPickup();

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMoodWeaponComponent> Weapon;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMoodPickUpComponent> Pickup;

	UFUNCTION()
	void PickedUp(ACharacter* Character);
};
