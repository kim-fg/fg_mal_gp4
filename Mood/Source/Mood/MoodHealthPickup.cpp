#include "MoodHealthPickup.h"
#include "Player/MoodCharacter.h"
#include "MoodHealthComponent.h"
#include <iostream>

AMoodHealthPickup::AMoodHealthPickup() {
    // You can add any additional initialization here if necessary
}

//MoodCharacter picks up the health pickup
void AMoodHealthPickup::PickedUp(ACharacter* Character) {
    //Call the base class pickup logic 
    Super::PickedUp(Character);

    if (Character == nullptr) {
        return;
    }

    //Cast the Character to AMoodCharacter to access the health component
    AMoodCharacter* MoodCharacter = Cast<AMoodCharacter>(Character);
    if (MoodCharacter) {
        //Get the health component of the character
        UMoodHealthComponent* HealthComponent = MoodCharacter->FindComponentByClass<UMoodHealthComponent>();
        if (HealthComponent) {
            //Increase the characters health by 400 TO TEST
            HealthComponent->Heal(400);
           
        }
    }
    //After the health is picked up, destroy the pickup actor
    Destroy();
}
