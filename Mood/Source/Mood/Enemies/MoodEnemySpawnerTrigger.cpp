#include "MoodEnemySpawnerTrigger.h"

#include "MoodEnemySpawner.h"
#include "Components/BoxComponent.h"
#include "Mood/Player/MoodCharacter.h"

AMoodEnemySpawnerTrigger::AMoodEnemySpawnerTrigger() {
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger Box");
	RootComponent = TriggerBox;

	TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMoodEnemySpawnerTrigger::OnBeginOverlap);	
}

void AMoodEnemySpawnerTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	auto Player = Cast<AMoodCharacter>(OtherActor);
	if (!Player) { return; }

	for	(auto i = 0; i < Spawners.Num(); i++) {
		auto Spawner = Spawners[i];
		if (!Spawner) {
			UE_LOG(LogTemp, Error, TEXT("%ls tried to start a null spawner, remove the element!"),
				*GetActorNameOrLabel());
			continue;
		}
		
		Spawners[i]->ActivateSpawning(Player);
	}

	TriggerBox->OnComponentBeginOverlap.RemoveAll(this);
}
