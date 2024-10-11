#include "MoodHealthPickup.h"
#include "Player/MoodCharacter.h"
#include "MoodHealthComponent.h"
#include "Components/StaticMeshComponent.h"

AMoodHealthPickup::AMoodHealthPickup() {
    //Default value for HealAmount, can be configured in the editor
    HealAmount = 400;

    //Create and attach the static mesh to represent the pickup
    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
    PickupMesh->SetupAttachment(RootComponent);
}

//MoodCharacter picks up the health pickup
void AMoodHealthPickup::PickedUp(ACharacter* Character) {
     Super::PickedUp(Character);

    if (Character == nullptr) {
        return;
    }

    //Cast the Character to AMoodCharacter to access the health component
    AMoodCharacter* MoodCharacter = Cast<AMoodCharacter>(Character);
    if (MoodCharacter) {
        // Get the health component of the character
        UMoodHealthComponent* HealthComponent = MoodCharacter->FindComponentByClass<UMoodHealthComponent>();
        if (HealthComponent) {
            //Use the configurable HealAmount
            HealthComponent->Heal(HealAmount);
        }
    }
    //After the health is picked up, destroy the pickup actor!
    Destroy();
}
