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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPawnSensingComponent> Sensing = nullptr;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMoodHealthComponent> Health = nullptr;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMoodWeaponSlotComponent> WeaponSlot = nullptr;
};
