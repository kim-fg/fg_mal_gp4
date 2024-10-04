#include "MoodHealthComponent.h"

void UMoodHealthComponent::Hurt(int Amount) {
	if (IsDead) { return; }
	
	Amount = abs(Amount);
	CurrentHealth -= Amount;
	if (CurrentHealth <= 0) {
		CurrentHealth = 0;
		IsDead = true;
		OnDeath.Broadcast();
	}
}

void UMoodHealthComponent::Heal(int Amount) {
	if (IsDead) { return; }
	
	Amount = abs(Amount);
	CurrentHealth += Amount;
	if (CurrentHealth > MaxHealth) {
		CurrentHealth = MaxHealth;
	}
}

void UMoodHealthComponent::BeginPlay() {
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;
}
