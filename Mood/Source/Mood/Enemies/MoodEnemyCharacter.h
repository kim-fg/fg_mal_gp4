#pragma once

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Mood/Player/MoodCharacter.h"
#include "MoodEnemyCharacter.generated.h"

class AMoodGameMode;
class UBehaviorTree;
class UPawnSensingComponent;
class UMoodWeaponSlotComponent;
class UMoodHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerSeen, AMoodCharacter*, Player);

UCLASS(Abstract)
class AMoodEnemyCharacter : public ACharacter {
	GENERATED_BODY()

public:
	AMoodEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	UMoodHealthComponent* GetHealth() { return Health; }
	
	//todo! make this protected
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UMoodHealthComponent> Health = nullptr;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerSeen OnPlayerSeen;

	UFUNCTION(BlueprintCallable)
	UMoodWeaponSlotComponent* GetWeaponSlot() { return WeaponSlot; }
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UMoodWeaponSlotComponent> WeaponSlot = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USphereComponent> ActivationSphere = nullptr;

	UFUNCTION()
	void LoseHealth(int Amount, int NewHealth);

private:
	UPROPERTY()
	AMoodGameMode* MoodGameMode = nullptr;
	
	UPROPERTY()
	TObjectPtr<AMoodCharacter> Player;

	bool CanSeePlayer();
	
	UFUNCTION()
	void OnActivationOverlap(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
	);
};
