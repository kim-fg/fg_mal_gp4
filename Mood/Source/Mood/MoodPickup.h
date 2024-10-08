#pragma once
#include "MoodPickUpComponent.h"
#include "MoodPickup.generated.h"

UCLASS(Abstract)
class AMoodPickup : public AActor {
	GENERATED_BODY()
public:
	AMoodPickup();

	UMoodPickUpComponent* GetPickup() { return Pickup; } 
protected:
	UFUNCTION()
	virtual void PickedUp(ACharacter* Character) {};

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMoodPickUpComponent> Pickup;
};
