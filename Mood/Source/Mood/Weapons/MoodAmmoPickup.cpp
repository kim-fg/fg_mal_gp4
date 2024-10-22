#include "MoodAmmoPickup.h"

#include "MoodWeaponSlotComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

AMoodAmmoPickup::AMoodAmmoPickup() {
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void AMoodAmmoPickup::PickedUp(ACharacter* Character) {
	if (!Character) { return; }

	auto WeaponSlot = Character->GetComponentByClass<UMoodWeaponSlotComponent>();
	if (!WeaponSlot) { return; }

	auto AmmoAdded = WeaponSlot->TryAddAmmo(Amount);
	if (!AmmoAdded) { return; }

	// Play pickup sound
	UGameplayStatics::PlaySound2D(GetWorld(), PickupSound);
	
	Destroy();
}
