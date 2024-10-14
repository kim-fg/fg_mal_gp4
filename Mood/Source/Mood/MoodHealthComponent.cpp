#include "MoodHealthComponent.h"

void UMoodHealthComponent::Hurt(int Amount) {
	if (IsDead) { return; }
	
	Amount = abs(Amount) * HealthLossPercent;
	CurrentHealth -= Amount;
	
	OnHurt.Broadcast(Amount, CurrentHealth);

	if (CurrentHealth < MaxHealth / 4) {
		bCanBeExecuted = true;
	}
	
	if (CurrentHealth <= 0) {
		CurrentHealth = 0;
		IsDead = true;
		OnDeath.Broadcast();
		return;
	}
}

void UMoodHealthComponent::Heal(int Amount) {
	if (IsDead) { return; }
	
	Amount = abs(Amount);
	CurrentHealth += Amount;
	if (CurrentHealth > MaxHealth) {
		CurrentHealth = MaxHealth;
	}

	//todo! technically doesnt send the actual health gain if it gets clamped
	OnHeal.Broadcast(Amount, CurrentHealth);
}

void UMoodHealthComponent::Reset() {
	IsDead = false;
	CurrentHealth = MaxHealth;
}

void UMoodHealthComponent::AlterHealthLoss(float Value) {
	HealthLossPercent = Value;
}

void UMoodHealthComponent::BeginPlay() {
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;
}
