#include "MoodWeaponPickup.h"

#include "MoodWeaponComponent.h"
#include "MoodWeaponSlotComponent.h"
#include "GameFramework/Character.h"

AMoodWeaponPickup::AMoodWeaponPickup() {
	Weapon = CreateDefaultSubobject<UMoodWeaponComponent>("Weapon");
	Weapon->SetupAttachment(RootComponent);
}

void AMoodWeaponPickup::PickedUp(ACharacter* Character) {
	if(!Character) { return; }
	
	auto WeaponSlot = Character->GetComponentByClass<UMoodWeaponSlotComponent>();
	if (!WeaponSlot) { return; }

	WeaponSlot->AddWeapon(Weapon);
}
