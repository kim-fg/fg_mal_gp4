#pragma once

#include "Mood/MoodPickup.h"
#include "MoodHealthPickup.generated.h"

class UMoodHealthComponent;
class ACharacter;

//Increases the players health by a configurable amount when picked up
UCLASS()
class AMoodHealthPickup : public AMoodPickup {
    GENERATED_BODY()

public:
    AMoodHealthPickup();

protected:
    virtual void PickedUp(ACharacter* Character) override;

private:
    //Configurable health increase amount
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Health", meta = (AllowPrivateAccess = "true"))
    int32 HealAmount;

    //Static mesh for the pickup
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Mesh", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> PickupMesh;
};
