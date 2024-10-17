#include "MoodEnemySpawner.h"

#include "MoodEnemyCharacter.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "Mood/MoodHealthComponent.h"

AMoodEnemySpawner::AMoodEnemySpawner() {
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(RootComponent);
	
	Billboard = CreateDefaultSubobject<UBillboardComponent>("Billboard");
	Billboard->SetupAttachment(RootComponent);
	Billboard->SetHiddenInGame(true);
	Billboard->SetRelativeLocation(FVector::UnitZ() * 150);
}

void AMoodEnemySpawner::ActivateSpawning(AMoodCharacter* InPlayer) {
	if (!EnemyToSpawn) {
		UE_LOG(LogTemp, Error, TEXT("Spawner does not have an enemy to spawn (%ls)"), *GetActorNameOrLabel());
		return;
	}

	Player = InPlayer;
	Spawn();
}

void AMoodEnemySpawner::Spawn() {
	auto SpawnParameters = FActorSpawnParameters{};
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	for (auto i = 0; i < EnemiesPerWave; i++) {
		auto SpawnLocation = GetActorLocation();
		auto SpawnRotation = GetActorRotation();
		auto SpawnedActor = GetWorld()->SpawnActor(EnemyToSpawn, &SpawnLocation, &SpawnRotation, SpawnParameters);
		auto Enemy = Cast<AMoodEnemyCharacter>(SpawnedActor);
		Enemy->SpawnDefaultController();
		Enemy->SetPlayer(Player);
		Enemy->GetHealth()->OnDeath.AddUniqueDynamic(this, &AMoodEnemySpawner::OnEnemyDeath);
		SpawnedEnemies.Push(Enemy);
	}
}

void AMoodEnemySpawner::OnEnemyDeath(AActor* DeadActor) {
	auto DeadEnemy = Cast<AMoodEnemyCharacter>(DeadActor);
	if (!DeadEnemy) {
		UE_LOG(LogTemp, Error, TEXT("Spawner caught a dead actor that wasn't an enemy, this is WEIRD!"));
		return;
	}
	
	SpawnedEnemies.Remove(DeadEnemy);

	if (SpawnedEnemies.Num() == 0) {
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &AMoodEnemySpawner::Spawn, RespawnDelay, false);
	}
}
