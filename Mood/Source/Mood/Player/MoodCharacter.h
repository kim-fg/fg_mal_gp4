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
	
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	float SprintingFOV = 110.f;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	float AlphaFOV = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	float ExecutionThresholdEnemyHP = 0.3f;
	UPROPERTY(EditDefaultsOnly)
	int ExecutionDamage = 5.f;
	UPROPERTY(EditDefaultsOnly)
	float ExecutionDistance = 600.f;
	UPROPERTY(EditDefaultsOnly)
	float MoveToExecuteTime = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	TEnumAsByte<ECollisionChannel> ClimbableChannel;
	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	TEnumAsByte<ECollisionChannel> InterruptClimbingChannel;
	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	float ClimbingTime = 1.f;
	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	FVector ClimbingLocation = FVector(50.f, 0.f, 150.f);
	
	void ToggleInteraction();
	
	UPROPERTY(BlueprintAssignable)
	FOnPaused OnPaused;
	
	UFUNCTION(BlueprintCallable)
	void ResetPlayer();
	
private:
	float WalkingSpeed;
	float WalkingFOV;
	float TimeSinceClimbStart = 0.f;
	UPROPERTY(EditDefaultsOnly)
	float ExecutionTimeDilation = 0.5f;

	float MoodSpeedPercent = 1.f;
	float MoodDamagePercent = 1.f;
	float CurrentMoodDamagePercent = 1.f;
	float MoodHealthLoss = 1.f;
	
	UPROPERTY(EditDefaultsOnly)
	float DeathFallSpeed = 20.f;

	UPROPERTY(EditDefaultsOnly)
	float CameraSpeed = 1.f;

	UPROPERTY(EditDefaultsOnly, Category=MoodMeter)
	float MoodChangeTimeDilation = 0.05f;
	UPROPERTY(EditDefaultsOnly, Category=MoodMeter)
	float MoodChangeAlpha = 0.01f;
	float CurrentTimeDilation = 1.f;
	bool bHasReachedTimeDilationBottom = false;

	bool bIsDead = false;
	bool bIsMidAir = false;
	bool bHasRespawned = false;
	bool bCanClimb = false;
	bool bIsExecuting = false;
	bool bIsChangingMood = false;

protected:
	void CheckPlayerState();

	UFUNCTION()
	void OnMoodChanged(EMoodState NewState);
	
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
	void KillPlayer();
	UFUNCTION()
	void RevivePlayer();
	void DeathCamMovement();
	
	void Sprint();
	void StopSprinting();

	void Execute();
	void ExecuteFoundEnemy();
	void ShootWeapon();
	void StopShootWeapon();

	void FindLedge();

	void MoodChanged();

	TEnumAsByte<EPlayerState> CurrentState;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	UPROPERTY()
	AMoodGameMode* MoodGameMode = nullptr;

	UPROPERTY()
	AMoodEnemyCharacter* Executee = nullptr;
	UPROPERTY()
	UMoodHealthComponent* ExecuteeHealth = nullptr;

public:
 	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};