#pragma once
#include "MoodEnemySpawner.generated.h"

class AMoodCharacter;
class AMoodEnemyCharacter;
class UArrowComponent;
class UBillboardComponent;


UCLASS(Abstract)
class AMoodEnemySpawner : public AActor {
    GENERATED_BODY()
public:
    AMoodEnemySpawner();

    UFUNCTION()
    void ActivateSpawning(AMoodCharacter* InPlayer);
    
protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
    TSubclassOf<AMoodEnemyCharacter> EnemyToSpawn = nullptr;

private:
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<USceneComponent> Root = nullptr;
    UPROPERTY()
    TObjectPtr<UArrowComponent> Arrow = nullptr;
    UPROPERTY(EditDefaultsOnly, Category=Editor)
    TObjectPtr<UBillboardComponent> Billboard = nullptr;

    TObjectPtr<AMoodCharacter> Player;
    
    UPROPERTY(EditDefaultsOnly, Category=Spawning)
    float RespawnDelay = 30.0f;
    UPROPERTY(EditDefaultsOnly, Category=Spawning)
    int EnemiesPerWave = 1;
    UFUNCTION()
    void Spawn();
    UPROPERTY()
    FTimerHandle SpawnTimer;
    TArray<TObjectPtr<AMoodEnemyCharacter>> SpawnedEnemies;
    UFUNCTION()
    void OnEnemyDeath(AActor* DeadActor);
};
