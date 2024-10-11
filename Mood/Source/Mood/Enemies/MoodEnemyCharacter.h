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

	UPROPERTY(BlueprintAssignable)
	FOnPlayerSeen OnPlayerSeen;

	UFUNCTION(BlueprintCallable)
	UMoodHealthComponent* GetHealth() { return Health; }
	UFUNCTION(BlueprintCallable)
	UMoodWeaponSlotComponent* GetWeaponSlot() { return WeaponSlot; }

	UFUNCTION(BlueprintCallable)
	bool CanSeePlayer();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UMoodHealthComponent> Health = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UMoodWeaponSlotComponent> WeaponSlot = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USphereComponent> ActivationSphere = nullptr;

	UFUNCTION()
	void LoseHealth(int Amount, int NewHealth);

private:
	void BeginPlay() override;
	
	UFUNCTION()
	void OnActivationOverlap(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
	);
	
	UPROPERTY()
	AMoodGameMode* MoodGameMode = nullptr;
	
	UPROPERTY()
	TObjectPtr<AMoodCharacter> Player;

	UFUNCTION(BlueprintCallable)
	void ScanForPlayer();
	FTimerHandle PlayerScanTimer;
};
