#pragma once

#include "MoodHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHeal, int, Amount, int, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHurt, int, Amount, int, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UMoodHealthComponent : public UActorComponent {
GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float HealthPercent() { return static_cast<float>(CurrentHealth) / MaxHealth;}

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;
	UPROPERTY(BlueprintAssignable)
	FOnHeal OnHeal;
	UPROPERTY(BlueprintAssignable)
	FOnHurt OnHurt;

	UFUNCTION(BlueprintCallable)
	void Hurt(int Amount);
	UFUNCTION(BlueprintCallable)
	void Heal(int Amount);
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	int MaxHealth = 100;
	int CurrentHealth = 0;
	bool IsDead = false;
};
