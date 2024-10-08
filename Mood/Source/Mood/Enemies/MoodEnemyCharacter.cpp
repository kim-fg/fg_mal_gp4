#include "MoodEnemyCharacter.h"
#include "Mood/MoodHealthComponent.h"
#include "Mood/Weapons/MoodWeaponSlotComponent.h"
#include "Perception/PawnSensingComponent.h"

AMoodEnemyCharacter::AMoodEnemyCharacter() {
	Sensing = CreateDefaultSubobject<UPawnSensingComponent>("Sensing");
	Health = CreateDefaultSubobject<UMoodHealthComponent>(TEXT("Health"));
	WeaponSlot = CreateDefaultSubobject<UMoodWeaponSlotComponent>(TEXT("Weapon Slot"));
}
