#include "MoodWeaponPickup.h"

#include "MoodWeaponComponent.h"
#include "MoodWeaponSlotComponent.h"
#include "Mood/MoodPickUpComponent.h"

AMoodWeaponPickup::AMoodWeaponPickup() {
	Weapon = CreateDefaultSubobject<UMoodWeaponComponent>("Weapon");
	RootComponent = Weapon;

	Pickup = CreateDefaultSubobject<UMoodPickUpComponent>("Pickup");
	Pickup->SetupAttachment(Weapon);
	Pickup->OnPickUp.AddDynamic(this, &AMoodWeaponPickup::PickedUp);
}

void AMoodWeaponPickup::PickedUp(ACharacter* Character) {
	if(!Character) { return; }
	
	auto WeaponSlot = Character->GetComponentByClass<UMoodWeaponSlotComponent>();
	if (!WeaponSlot) { return; }

	WeaponSlot->AddWeapon(Weapon);
}
