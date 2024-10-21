// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Mood/MoodGameMode.h"
#include "MoodCharacter.generated.h"

class AMoodEnemyCharacter;
class UMoodShotgunCameraShake;
class UMoodWeaponComponent;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UBoxComponent;
class UInputAction;
class UInputMappingContext;
class UMoodWeaponSlotComponent;
class UMoodHealthComponent;
class AMoodGameMode;
struct FInputActionValue;
enum EMoodState;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

enum EPlayerState
{
	Eps_Idle,
	Eps_Walking,
	Eps_Sprinting,
	Eps_ClimbingLedge,
	Eps_NoControl
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPaused);

UCLASS(config=Game)
class AMoodCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	
	/** Health Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UMoodHealthComponent* HealthComponent;
	
	/** Weapon Slot Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UMoodWeaponSlotComponent* WeaponSlotComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ClimbAction;
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ShootAction;
	/** Weapon selected by scrolling wheel */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ScrollWeaponAction;
	/** Weapon selected by buttons 1-3 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SelectWeapon1Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SelectWeapon2Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SelectWeapon3Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ExecuteAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

public:
	AMoodCharacter();

protected:
	virtual void BeginPlay();
	
	virtual void Tick(float DeltaTime) override;

	virtual void Landed(const FHitResult& Hit) override;

public:
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly)
	float SprintingSpeed = 600.f;
	
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	TSubclassOf<UCameraShakeBase> IdleHeadBob;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	TSubclassOf<UCameraShakeBase> WalkHeadBob;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	TSubclassOf<UCameraShakeBase> SprintHeadBob;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	TSubclassOf<UCameraShakeBase> ClimbHeadBob;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	TSubclassOf<UCameraShakeBase> LandShake;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	TSubclassOf<UCameraShakeBase> ExecuteShake;
	
	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	TEnumAsByte<ECollisionChannel> ClimbableChannel;
	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	TEnumAsByte<ECollisionChannel> InterruptClimbingChannel;
	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	float ClimbingTime = 1.f;
	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	FVector ClimbingLocation = FVector(50.f, 0.f, 150.f);
	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	FVector ReachLedgeLocation = FVector(80.f, 0.f, 50.f);

	UPROPERTY(BlueprintReadOnly, Category=Execution)
	bool bHasFoundExecutableEnemy = false;
	
	void ToggleInteraction();
	
	UPROPERTY(BlueprintAssignable)
	FOnPaused OnPaused;
	
	UFUNCTION(BlueprintCallable)
	void ResetPlayer();
	
private:
	float WalkingSpeed;
	float WalkingFOV;
	float TimeSinceClimbStart = 0.f;
	
	float MoodSpeedPercent = 1.f;
	float MoodDamagePercent = 1.f;
	float CurrentMoodDamagePercent = 1.f;
	float MoodHealthLoss = 1.f;
	
	UPROPERTY(EditDefaultsOnly)
	float DeathFallSpeed = 20.f;

	// Default camera speed is multiplied by this number
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	float CameraSpeed = 1.f;

	// Camera speed is multiplied by this number 
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	float SlowMotionCameraSpeed = 0.1f;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	float MaxTimeInSlowMotion = 1.5f;
	float SlowMotionTime = 0.f;

		
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	float SprintingFOV = 110.f;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	float AlphaFOV = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, Category=Execution)
	float ExecutionTimeDilation = 0.5f;
	UPROPERTY(EditDefaultsOnly, Category=Execution)
	float ExecutionThresholdEnemyHP = 0.3f;
	UPROPERTY(EditDefaultsOnly, Category=Execution)
	int ExecutionDamage = 5.f;
	UPROPERTY(EditDefaultsOnly, Category=Execution)
	float ExecutionDistance = 600.f;
	UPROPERTY(EditDefaultsOnly, Category=Execution)
	float MoveToExecuteTime = 0.1f;
	// How much to heal the player when executing 
	UPROPERTY(EditDefaultsOnly, Category=Execution)
	int ExecutionHealing = 5;
	FVector ExecuteeLocation = FVector(0, 0, 0);

	bool bIsDead = false;
	bool bIsMidAir = false;
	bool bHasRespawned = false;
	bool bCanClimb = false;
	bool bIsExecuting = false;
	bool bIsSlowMotion = false;

protected:
	void CheckPlayerState();

	UFUNCTION()
	void OnMoodChanged(EMoodState NewState);
	UFUNCTION()
	void OnSlowMotionTriggered(EMoodState NewState);

	void PlaySlowMotion(); 
	
	void AttemptClimb();
	void DontClimb();
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for weapon scrolling input */
	void WeaponScroll(const FInputActionValue& Value);
	void SelectWeapon1();
	void SelectWeapon2();
	void SelectWeapon3();

	void PauseGame();

	UFUNCTION()
	void ShootCameraShake(UMoodWeaponComponent* Weapon);

	UFUNCTION()
	void LoseHealth(int Amount, int NewHealth);
	UFUNCTION()
	void KillPlayer(AActor* DeadActor);
	UFUNCTION()
	void RevivePlayer();
	void DeathCamMovement();
	
	void Sprint();
	void StopSprinting();

	void FindExecutee();
	void ToggleExecute();
	void ExecuteFoundEnemy();
	void ShootWeapon();
	void StopShootWeapon();

	void FindLedge();
	
	TEnumAsByte<EPlayerState> CurrentState;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	UPROPERTY()
	AMoodGameMode* MoodGameMode = nullptr;

	UPROPERTY()
	AActor* FoundActor = nullptr;
	UPROPERTY()
	AMoodEnemyCharacter* Executee = nullptr;
	UPROPERTY()
	UMoodHealthComponent* ExecuteeHealth = nullptr;

public:
 	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};