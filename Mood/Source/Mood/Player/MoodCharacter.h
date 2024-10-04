// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MoodCharacter.generated.h"

class UMoodWeaponComponent;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UBoxComponent;
class UInputAction;
class UInputMappingContext;
class UMoodWeaponSlotComponent;
class UMoodHealthComponent;
// class UCameraShake;
// class UCameraShake
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

enum EPlayerState
{
	Eps_Idle,
	Eps_Walking,
	Eps_Sprinting,
	Eps_MeleeAttacking,
	Eps_ClimbingLedge
};

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
	
	/** Melee attack box */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* MeleeAttackBoxComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SprintAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MeleeAttackAction;
	
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

public:
	AMoodCharacter();

	TEnumAsByte<EPlayerState> CurrentState;

protected:
	virtual void BeginPlay();
	
	virtual void Tick(float DeltaTime) override;

public:
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly)
	float SprintingSpeed = 600.f;

	UPROPERTY(EditDefaultsOnly, Category=Camera)
	TSubclassOf<UCameraShakeBase> GunCameraShake;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	TSubclassOf<UCameraShakeBase> ShotgunCameraShake;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	TSubclassOf<UCameraShakeBase> IdleHeadBob;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	TSubclassOf<UCameraShakeBase> WalkHeadBob;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	TSubclassOf<UCameraShakeBase> SprintHeadBob;
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	TSubclassOf<UCameraShakeBase> ClimbHeadBob;
	
	UPROPERTY(EditDefaultsOnly, Category=Camera)
	float SprintingFOV = 110.f;

	UPROPERTY(EditDefaultsOnly, Category=Camera)
	float AlphaFOV = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	float MeleeAttackCooldown = 1.f;

	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	TEnumAsByte<ECollisionChannel> ClimbableChannel;
	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	TEnumAsByte<ECollisionChannel> InterruptClimbingChannel;
	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	float ClimbingTime = 1.f;
	UPROPERTY(EditDefaultsOnly, Category=Climbing)
	FVector ClimbingLocation = FVector(50.f, 0.f, 150.f);

	// UFUNCTION(Blueprintable)
	void Interact();

	
private:
	float WalkingSpeed;
	float WalkingFOV;
	float TimeSinceMeleeAttack = 1.f;
	float TimeSinceClimbStart = 0.f;

protected:
	void CheckPlayerState();
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for weapon scrolling input */
	void WeaponScroll(const FInputActionValue& Value);
	void SelectWeapon1();
	void SelectWeapon2();
	void SelectWeapon3();

	UFUNCTION()
	void ShootCameraShake(UMoodWeaponComponent* Weapon);
	
	void Sprint();
	void StopSprinting();

	void MeleeAttack();
	void ShootWeapon();
	void StopShootWeapon();

	void FindLedge();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
 	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};