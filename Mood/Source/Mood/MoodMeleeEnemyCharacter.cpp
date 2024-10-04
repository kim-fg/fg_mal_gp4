#include "MoodMeleeEnemyCharacter.h"

#include "MoodHealthComponent.h"
#include "MoodMeleeEnemyAIController.h"


// Sets default values
AMoodMeleeEnemyCharacter::AMoodMeleeEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AMoodMeleeEnemyAIController::StaticClass();
	healthComp = CreateDefaultSubobject<UMoodHealthComponent>(TEXT("healthComp"));

}

// Called when the game starts or when spawned
void AMoodMeleeEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoodMeleeEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMoodMeleeEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

