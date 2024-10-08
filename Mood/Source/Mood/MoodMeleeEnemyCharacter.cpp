#include "MoodMeleeEnemyCharacter.h"

#include "MoodHealthComponent.h"
#include "Components/SphereComponent.h"
#include "Player/MoodCharacter.h"
#include "Weapons/MoodWeaponSlotComponent.h"


// Sets default values
AMoodMeleeEnemyCharacter::AMoodMeleeEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	attackradius = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRadius"));
	attackradius->OnComponentBeginOverlap.AddDynamic(this, &AMoodMeleeEnemyCharacter::HandleBeginOverlap);
	attackradius->OnComponentEndOverlap.AddDynamic(this, &AMoodMeleeEnemyCharacter::HandleEndOverlap);
	attackradius->SetSphereRadius(1500.f);

	
	
	healthComp = CreateDefaultSubobject<UMoodHealthComponent>(TEXT("healthComp"));
	
	WeaponSlotComponent = CreateDefaultSubobject<UMoodWeaponSlotComponent>(TEXT("WeaponSlotComponent"));

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


void AMoodMeleeEnemyCharacter::HandleBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if(AMoodCharacter* moodCharacter = Cast<AMoodCharacter>(OtherActor))
	{
		// WeaponSlotComponent->SetTriggerHeld(true);
		// UE_LOG(LogTemp, Warning, TEXT("Overlapping"));
	}
}


void AMoodMeleeEnemyCharacter::HandleEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
}


