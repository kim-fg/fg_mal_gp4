#include "MoodEnemyCharacter.h"

#include "Components/SphereComponent.h"
#include "Mood/MoodGameMode.h"
#include "Mood/MoodHealthComponent.h"
#include "Mood/Weapons/MoodWeaponSlotComponent.h"

AMoodEnemyCharacter::AMoodEnemyCharacter() {
	ActivationSphere = CreateDefaultSubobject<USphereComponent>("Activation Sphere");
	ActivationSphere->SetupAttachment(RootComponent);
	
	Health = CreateDefaultSubobject<UMoodHealthComponent>(TEXT("Health"));
	WeaponSlot = CreateDefaultSubobject<UMoodWeaponSlotComponent>(TEXT("Weapon Slot"));
}

void AMoodEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	MoodGameMode = Cast<AMoodGameMode>(GetWorld()->GetAuthGameMode());
	
	Health->OnHurt.AddUniqueDynamic(this, &AMoodEnemyCharacter::LoseHealth);
}

void AMoodEnemyCharacter::LoseHealth(int Amount, int NewHealth)
{
	MoodGameMode->ChangeMoodValue(Amount);
}