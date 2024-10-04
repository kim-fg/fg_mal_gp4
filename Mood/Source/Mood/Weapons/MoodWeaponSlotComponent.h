#pragma once

#include "CoreMinimal.h"
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

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasWeapon() { return Weapons.Num() > 0; }

	void EnableSelectedWeapon();
	void SelectNextWeapon();
	void SelectPreviousWeapon();
	void SelectWeapon(int Index);

	UFUNCTION()
	USceneComponent* GetMuzzleRoot() { return MuzzleRoot; }
	UFUNCTION()
	void SetMuzzleRoot(USceneComponent* InMuzzleRoot) { MuzzleRoot = InMuzzleRoot; }
	
	UFUNCTION(BlueprintCallable)
	void SetTriggerHeld(bool InTriggerHeld) {
		TriggerHeld = InTriggerHeld;
	}
private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AMoodWeaponPickup>> DefaultWeapons = {};
	
	void UseSelectedWeapon();

	TObjectPtr<ACharacter> Owner;
	TObjectPtr<USceneComponent> MuzzleRoot;
	
	int SelectedWeaponIndex = 0;
	bool TriggerHeld = false;
	
	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditDefaultsOnly, Category=Gameplay)
	FVector MuzzleOffset;
	
	UPROPERTY(EditDefaultsOnly)
	bool AutoSelectNewWeapon = true;

	UPROPERTY(VisibleInstanceOnly)
	TArray<UMoodWeaponComponent*> Weapons = {};
};
