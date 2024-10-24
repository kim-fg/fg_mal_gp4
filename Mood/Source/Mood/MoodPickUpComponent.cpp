#include "MoodPickUpComponent.h"
#include "Player/MoodCharacter.h"

UMoodPickUpComponent::UMoodPickUpComponent() {
	// Setup the Sphere Collision
	// SphereRadius = 32.f;
}

void UMoodPickUpComponent::BeginPlay() {
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UMoodPickUpComponent::OnSphereBeginOverlap);
}

void UMoodPickUpComponent::OnSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult
) {
	// Checking if it is a First Person Character overlapping
	AMoodCharacter* Character = Cast<AMoodCharacter>(OtherActor);
	if (Character != nullptr) {
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);
	}
}
