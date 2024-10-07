#include "MoodAmmoPickup.h"

#include "MoodWeaponSlotComponent.h"
AMoodAmmoPickup::AMoodAmmoPickup() {}

void AMoodAmmoPickup::PickedUp(ACharacter* Character) {
	if (!Character) { return; }

	auto WeaponSlot = Character->GetComponentByClass<UMoodWeaponSlotComponent>();
	if (!WeaponSlot) { return; }

	WeaponSlot->AddAmmo(WeaponType, Amount);
}
