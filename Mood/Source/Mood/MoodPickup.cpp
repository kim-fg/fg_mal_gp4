#include "MoodPickup.h"
#include "MoodPickUpComponent.h"

AMoodPickup::AMoodPickup() {
	Pickup = CreateDefaultSubobject<UMoodPickUpComponent>("Pickup");
	RootComponent = Pickup;

	Pickup->OnPickUp.AddDynamic(this, &AMoodPickup::PickedUp);
}
