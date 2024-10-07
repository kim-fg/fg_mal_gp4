#pragma once
#include "Mood/MoodPickup.h"
#include "MoodWeaponPickup.generated.h"

class UMoodPickUpComponent;
class UMoodWeaponComponent;

UCLASS(Abstract)
class AMoodWeaponPickup : public AMoodPickup {
	GENERATED_BODY()
public:
	AMoodWeaponPickup();

	UFUNCTION(BlueprintCallable)
	UMoodWeaponComponent* GetWeapon() { return Weapon; }
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMoodWeaponComponent> Weapon;

	UFUNCTION()
	virtual void PickedUp(ACharacter* Character) override;
};
