#pragma once

#include "MoodEnemySpawnerTrigger.generated.h" 

class AMoodEnemySpawner;
class UBoxComponent;

UCLASS(Abstract)
class AMoodEnemySpawnerTrigger : public AActor {
	GENERATED_BODY()
public:
	AMoodEnemySpawnerTrigger();
private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditInstanceOnly)
	TArray<TObjectPtr<AMoodEnemySpawner>> Spawners;

	UPROPERTY(EditInstanceOnly)
	TObjectPtr<UBoxComponent> TriggerBox;
};
