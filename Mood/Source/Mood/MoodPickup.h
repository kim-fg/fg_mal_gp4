#pragma once
#include "MoodPickup.generated.h"

class UMoodPickUpComponent;

UCLASS(Abstract)
class AMoodPickup : public AActor {
	GENERATED_BODY()
public:
	AMoodPickup();

	UMoodPickUpComponent* GetPickup() { return Pickup; } 
protected:
	UFUNCTION()
	virtual void PickedUp(ACharacter* Character);

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMoodPickUpComponent> Pickup;
};
