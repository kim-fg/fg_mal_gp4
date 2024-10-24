#pragma once

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "MoodPickUpComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, ACharacter*, PickUpCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UMoodPickUpComponent : public UBoxComponent {
	GENERATED_BODY()

public:
	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPickUp OnPickUp;

	UMoodPickUpComponent();

	UFUNCTION(BlueprintCallable)
	void DisableInteraction() { OnComponentBeginOverlap.RemoveAll(this); }

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Code for when something overlaps this component */
	UFUNCTION()
	void OnSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	    const FHitResult& SweepResult
	);
};
