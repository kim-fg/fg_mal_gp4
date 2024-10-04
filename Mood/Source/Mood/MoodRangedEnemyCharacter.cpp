#include "MoodRangedEnemyCharacter.h"
#include "MoodRangedEnemyAIController.h"
#include "MoodHealthComponent.h"


// Sets default values
AMoodRangedEnemyCharacter::AMoodRangedEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AMoodRangedEnemyAIController::StaticClass();
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

// Called to bind functionality to input
void AMoodRangedEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

