#pragma once
#include "MoodPickup.generated.h"

class UMoodPickUpComponent;

UCLASS(Abstract)
class AMoodPickup : public AActor {
	GENERATED_BODY()
public:
	AMoodPickup();

	UFUNCTION()
	void Disable();
	
	UMoodPickUpComponent* GetPickup() { return Pickup; } 
protected:
	UFUNCTION()
	virtual void PickedUp(ACharacter* Character);
	
	UPROPERTY(EditDefaultsOnly, Category=Sound)
	USoundBase* PickupSound;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMoodPickUpComponent> Pickup;
};
