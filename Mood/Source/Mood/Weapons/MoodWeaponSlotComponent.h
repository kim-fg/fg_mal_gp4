#pragma once

#include "CoreMinimal.h"
#include "MoodAmmoPickup.h"
#include "MoodWeaponSlotComponent.generated.h"

class AMoodWeaponPickup;
class UMoodWeaponComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponUsed, UMoodWeaponComponent*, Weapon);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMoodWeaponSlotComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UMoodWeaponSlotComponent();

	UPROPERTY(BlueprintAssignable)
	FOnWeaponUsed OnWeaponUsed;

	UFUNCTION(BlueprintCallable)
	bool AddWeapon(UMoodWeaponComponent* Weapon);

	UFUNCTION(BlueprintCallable)
	void SetDamageMultiplier(float InDamageMultiplier) {
		if (InDamageMultiplier < 1.0f) { InDamageMultiplier = 1.0f; }
		DamageMultiplier = InDamageMultiplier;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasWeapon() { return Weapons.Num() > 0; }
	void SelectNextWeapon();
	void SelectPreviousWeapon();
	void SelectWeapon(int Index);

	UMoodWeaponComponent* GetSelectedWeapon();

	UFUNCTION(BlueprintCallable)
	USceneComponent* GetMuzzleRoot() { return MuzzleRoot; }
	UFUNCTION(BlueprintCallable)
	void SetMuzzleRoot(USceneComponent* InMuzzleRoot) { MuzzleRoot = InMuzzleRoot; }
	
	UFUNCTION(BlueprintCallable)
	void SetTriggerHeld(bool InTriggerHeld) {
		TriggerHeld = InTriggerHeld;
	}

	UFUNCTION(BlueprintCallable)
	bool TryAddAmmo(int Amount);

	UFUNCTION()
	TArray<UMoodWeaponComponent*> GetWeaponArray();

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AMoodWeaponPickup>> DefaultWeapons = {};

	void EnableSelectedWeapon();
	void UseSelectedWeapon();

	UPROPERTY()
	TObjectPtr<ACharacter> Owner = nullptr;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> MuzzleRoot = nullptr;
	
	int SelectedWeaponIndex = 0;
	bool TriggerHeld = false;
	float DamageMultiplier = 1.0f;
	
	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditDefaultsOnly, Category=Gameplay)
	FVector MuzzleOffset = {0.0f, 0.0f, 0.0f};
	
	UPROPERTY(EditDefaultsOnly)
	bool AutoSelectNewWeapon = true;

	UPROPERTY(VisibleInstanceOnly)
	TArray<UMoodWeaponComponent*> Weapons = {};
};
