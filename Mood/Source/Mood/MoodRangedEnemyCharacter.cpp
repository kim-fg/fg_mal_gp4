#include "MoodRangedEnemyCharacter.h"

#include "MoodHealthComponent.h"


// Sets default values
AMoodRangedEnemyCharacter::AMoodRangedEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	healthComp = CreateDefaultSubobject<UMoodHealthComponent>(TEXT("healthComp"));

}

// Called when the game starts or when spawned
void AMoodRangedEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoodRangedEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

