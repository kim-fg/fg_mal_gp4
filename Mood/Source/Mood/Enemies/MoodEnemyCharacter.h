#pragma once

#include "GameFramework/Character.h"
#include "MoodEnemyCharacter.generated.h"

class UBehaviorTree;
class UPawnSensingComponent;
class UMoodWeaponSlotComponent;
class UMoodHealthComponent;

UCLASS(Abstract)
class AMoodEnemyCharacter : public ACharacter {
	GENERATED_BODY()

public:
	AMoodEnemyCharacter();
	
	UFUNCTION(BlueprintCallable)
	UMoodHealthComponent* GetHealth() { return Health; }
	
	//todo! make this protected
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UMoodHealthComponent> Health = nullptr;

	UFUNCTION(BlueprintCallable)
	UMoodWeaponSlotComponent* GetWeaponSlot() { return WeaponSlot; }
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPawnSensingComponent> Sensing = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UMoodWeaponSlotComponent> WeaponSlot = nullptr;
};
