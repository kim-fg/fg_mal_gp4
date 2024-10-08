#pragma once
#include "Mood/MoodPickup.h"
#include "MoodAmmoPickup.generated.h"

class UMoodPickUpComponent;
class AMoodWeaponPickup;
class UMoodWeaponComponent;

UCLASS(Abstract)
class AMoodAmmoPickup : public AMoodPickup {
	GENERATED_BODY()
public:
	AMoodAmmoPickup();
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	int Amount = 10;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMoodWeaponPickup> WeaponType;

	void PickedUp(ACharacter* Character) override;
};
