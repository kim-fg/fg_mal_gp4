#pragma once

#include "Mood/MoodPickup.h"
#include "MoodHealthPickup.generated.h"

class UMoodHealthComponent;
class ACharacter;
//Increases the players health by 10 when picked up

UCLASS()
class AMoodHealthPickup : public AMoodPickup {
    GENERATED_BODY()

public:
    AMoodHealthPickup();

protected:
    virtual void PickedUp(ACharacter* Character) override;
};
