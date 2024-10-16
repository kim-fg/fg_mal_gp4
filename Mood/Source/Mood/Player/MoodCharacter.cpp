// Copyright Epic Games, Inc. All Rights Reserved.

#include "MoodCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Weapons/MoodWeaponSlotComponent.h"
#include "../MoodHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Mood/MoodGameMode.h"
#include "Mood/Enemies/MoodEnemyCharacter.h"
#include "Mood/Weapons/MoodWeaponComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMoodCharacter

AMoodCharacter::AMoodCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Our original components 
	GetMesh()->SetupAttachment(FirstPersonCameraComponent);
	HealthComponent = CreateDefaultSubobject<UMoodHealthComponent>(TEXT("HealthComponent"));
	WeaponSlotComponent = CreateDefaultSubobject<UMoodWeaponSlotComponent>(TEXT("WeaponSlotComponent"));
	WeaponSlotComponent->SetMuzzleRoot(FirstPersonCameraComponent);
}

void AMoodCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(MoodGameMode))
	{
		MoodGameMode = Cast<AMoodGameMode>(GetWorld()->GetAuthGameMode());
		MoodGameMode->OnMoodChanged.AddUniqueDynamic(this, &AMoodCharacter::OnMoodChanged);
		MoodGameMode->OnSlowMotionTriggered.AddUniqueDynamic(this, &AMoodCharacter::OnSlowMotionTriggered);
	}

	WalkingSpeed = GetCharacterMovement()->MaxWalkSpeed;
	WalkingFOV = FirstPersonCameraComponent->FieldOfView;

	HealthComponent->OnHurt.AddUniqueDynamic(this, &AMoodCharacter::LoseHealth);
	HealthComponent->OnDeath.AddUniqueDynamic(this, &AMoodCharacter::KillPlayer);
	WeaponSlotComponent->OnWeaponUsed.AddUniqueDynamic(this, &AMoodCharacter::ShootCameraShake);
}

void AMoodCharacter::Tick(float const DeltaTime)
{
	Super::Tick(DeltaTime);

	bIsMidAir = GetCharacterMovement()->Velocity.Z != 0 ? 1 : 0;

	CheckPlayerState();
	FindLedge();
	PlaySlowMotion();
	// MoodChanged();
}

void AMoodCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	auto PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) { return; }

	PlayerController->PlayerCameraManager->StartCameraShake(LandShake, 1.0f);
}

//////////////////////////////////////////////////////////////////////////// Input

void AMoodCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Climbing
		EnhancedInputComponent->BindAction(ClimbAction, ETriggerEvent::Started, this, &AMoodCharacter::AttemptClimb);
		EnhancedInputComponent->BindAction(ClimbAction, ETriggerEvent::Completed, this, &AMoodCharacter::DontClimb);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMoodCharacter::Move);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AMoodCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this,
		                                   &AMoodCharacter::StopSprinting);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMoodCharacter::Look);

		// Attacking
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AMoodCharacter::ShootWeapon);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Canceled, this,
		                                   &AMoodCharacter::StopShootWeapon);
		EnhancedInputComponent->BindAction(ExecuteAction, ETriggerEvent::Triggered, this, &AMoodCharacter::Execute);

		// Weapon Selection
		EnhancedInputComponent->BindAction(ScrollWeaponAction, ETriggerEvent::Triggered, this,
		                                   &AMoodCharacter::WeaponScroll);
		EnhancedInputComponent->BindAction(SelectWeapon1Action, ETriggerEvent::Triggered, this,
		                                   &AMoodCharacter::SelectWeapon1);
		EnhancedInputComponent->BindAction(SelectWeapon2Action, ETriggerEvent::Triggered, this,
		                                   &AMoodCharacter::SelectWeapon2);
		EnhancedInputComponent->BindAction(SelectWeapon3Action, ETriggerEvent::Triggered, this,
		                                   &AMoodCharacter::SelectWeapon3);

		// Interact 
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this,
		                                   &AMoodCharacter::ToggleInteraction);

		// Pausing
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AMoodCharacter::PauseGame);
	}

	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void AMoodCharacter::CheckPlayerState()
{
	switch (CurrentState)
	{
	case Eps_Idle:
		FirstPersonCameraComponent->FieldOfView = FMath::Lerp(FirstPersonCameraComponent->FieldOfView, WalkingFOV,
		                                                      AlphaFOV);
		if (!bIsMidAir)
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(IdleHeadBob, 1.f);
		if (GetCharacterMovement()->Velocity != FVector(0, 0, 0))
			CurrentState = Eps_Walking;
		break;
	case Eps_Walking:
		FirstPersonCameraComponent->FieldOfView = FMath::Lerp(FirstPersonCameraComponent->FieldOfView, WalkingFOV,
		                                                      AlphaFOV);
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		if (!bIsMidAir)
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(WalkHeadBob, 1.f);
		if (GetCharacterMovement()->Velocity.Length() < 10.f)
			CurrentState = Eps_Idle;
		break;
	case Eps_Sprinting:
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
		FirstPersonCameraComponent->FieldOfView = FMath::Lerp(FirstPersonCameraComponent->FieldOfView, SprintingFOV,
		                                                      AlphaFOV);
		if (!bIsMidAir)
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(SprintHeadBob, 1.f);
		if (GetCharacterMovement()->Velocity.Length() < 10.f)
			StopSprinting();
		break;
	case Eps_ClimbingLedge:
		GetCharacterMovement()->Velocity = FVector(0, 0, 0);
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(WalkHeadBob, 1.f);
		StopShootWeapon();
		TimeSinceClimbStart += GetWorld()->DeltaTimeSeconds;
		if (TimeSinceClimbStart >= ClimbingTime)
			CurrentState = Eps_Walking;
		break;
	case Eps_NoControl:
		StopShootWeapon();
		DeathCamMovement();
		ExecuteFoundEnemy();
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("No player state found. MoodCharacter.cpp - CheckPlayerState"));
		CurrentState = Eps_Idle;
		break;
	}
}

void AMoodCharacter::OnMoodChanged(EMoodState NewState)
{
	switch (NewState)
	{
	case Ems_Mood666:
		MoodSpeedPercent = 1.5f;
		MoodDamagePercent = 2.5f;
		MoodHealthLoss = 0.5f;
		break;
	case Ems_Mood444:
		MoodSpeedPercent = 1.2f;
		MoodDamagePercent = 1.8f;
		MoodHealthLoss = 0.8f;
		break;
	case Ems_Mood222:
		MoodSpeedPercent = 1.1f;
		MoodDamagePercent = 1.3f;
		MoodHealthLoss = 0.9f;
		break;
	case Ems_NoMood:
		MoodSpeedPercent = 1.f;
		MoodDamagePercent = 1.f;
		MoodHealthLoss = 1.f;
		break;
	default:
		return;
	}

	WeaponSlotComponent->SetDamageMultiplier(MoodDamagePercent);
	HealthComponent->AlterHealthLoss(MoodHealthLoss);
}

void AMoodCharacter::OnSlowMotionTriggered(EMoodState NewState)
{
	bIsSlowMotion = true;
}

void AMoodCharacter::PlaySlowMotion()
{
	if (bIsSlowMotion)
	{
		SlowMotionTime += GetWorld()->DeltaTimeSeconds;
		if (SlowMotionTime >= 2.5f)
		{
			bIsSlowMotion = false;
			SlowMotionTime = 0.f;
		}
	}
}

void AMoodCharacter::AttemptClimb()
{
	bCanClimb = true;
}

void AMoodCharacter::DontClimb()
{
	bCanClimb = false;
}

void AMoodCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr && CurrentState != Eps_NoControl)
	{
		const FVector2D MoodSpeed = MovementVector * MoodSpeedPercent;
		AddMovementInput(GetActorForwardVector(), MoodSpeed.Y);
		AddMovementInput(GetActorRightVector(), MoodSpeed.X);
	}
}

void AMoodCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr && CurrentState != Eps_NoControl)
	{
		FVector2D TotalLookAxis = LookAxisVector * CameraSpeed;

		if (bIsSlowMotion)
			TotalLookAxis *= SlowMotionCameraSpeed;
		
		AddControllerYawInput(TotalLookAxis.X);
		AddControllerPitchInput(TotalLookAxis.Y);
	}
}

void AMoodCharacter::WeaponScroll(const FInputActionValue& Value)
{
	if (WeaponSlotComponent == nullptr || !WeaponSlotComponent->HasWeapon())
		return;

	const float ScrollDirection = Value.Get<float>();

	if (ScrollDirection > 0)
		WeaponSlotComponent->SelectNextWeapon();
	else if (ScrollDirection < 0)
		WeaponSlotComponent->SelectPreviousWeapon();
}

void AMoodCharacter::SelectWeapon1()
{
	if (WeaponSlotComponent == nullptr || !WeaponSlotComponent->HasWeapon())
		return;

	WeaponSlotComponent->SelectWeapon(0);
}

void AMoodCharacter::SelectWeapon2()
{
	if (WeaponSlotComponent == nullptr || !WeaponSlotComponent->HasWeapon())
		return;

	WeaponSlotComponent->SelectWeapon(1);
}

void AMoodCharacter::SelectWeapon3()
{
	if (WeaponSlotComponent == nullptr || !WeaponSlotComponent->HasWeapon())
		return;

	WeaponSlotComponent->SelectWeapon(2);
}

void AMoodCharacter::PauseGame()
{
	OnPaused.Broadcast();
}

void AMoodCharacter::ShootCameraShake(UMoodWeaponComponent* Weapon)
{
	auto PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) { return; }

	PlayerController->PlayerCameraManager->StartCameraShake(Weapon->GetRecoilCameraShake(), 1.0f);
}

void AMoodCharacter::LoseHealth(int Amount, int NewHealth)
{
	MoodGameMode->ChangeMoodValue(-Amount);
}

void AMoodCharacter::ToggleInteraction()
{
}

void AMoodCharacter::ResetPlayer()
{
	bHasRespawned = true;
}

void AMoodCharacter::Sprint()
{
	if (GetCharacterMovement()->Velocity.Length() > 10.f
		&& CurrentState != Eps_ClimbingLedge
		&& CurrentState != Eps_NoControl)
	{
		CurrentState = Eps_Sprinting;
	}
}

void AMoodCharacter::StopSprinting()
{
	CurrentState = Eps_Walking;
}

void AMoodCharacter::Execute()
{
	if (CurrentState == Eps_ClimbingLedge || CurrentState == Eps_NoControl)
		return;

	FHitResult HitResult;
	FCollisionQueryParams Parameters;
	Parameters.AddIgnoredActor(this);

	const FVector TraceStart = FirstPersonCameraComponent->GetComponentLocation();
	const FVector TraceEnd = FirstPersonCameraComponent->GetComponentLocation()
		+ FirstPersonCameraComponent->GetForwardVector() * ExecutionDistance;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, InterruptClimbingChannel, Parameters,
	                                         FCollisionResponseParams()))
	{
		Executee = Cast<AMoodEnemyCharacter>(HitResult.GetActor());
		if (!IsValid(Executee))
			return;

		ExecuteeHealth = Cast<UMoodHealthComponent>(Executee->FindComponentByClass<UMoodHealthComponent>());
		if (!IsValid(ExecuteeHealth))
			return;

		if (ExecuteeHealth->HealthPercent() <= ExecutionThresholdEnemyHP)
		{
			bIsExecuting = true;
			CurrentState = Eps_NoControl;
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = Owner;

			UKismetSystemLibrary::MoveComponentTo(
				RootComponent,
				Executee->GetActorLocation(),
				GetActorRotation(),
				false,
				false,
				MoveToExecuteTime,
				true,
				EMoveComponentAction::Move,
				LatentInfo
			);
		}
	}
}

void AMoodCharacter::ExecuteFoundEnemy()
{
	if (!bIsExecuting)
		return;

	if (IsValid(Executee) && IsValid(ExecuteeHealth))
	{
		GetCharacterMovement()->Velocity = FVector(0, 0, 0);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), ExecutionTimeDilation);

		if ((Executee->GetActorLocation() - GetActorLocation()).Length() < 100.f)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(ExecuteShake, 1.f);
			ExecuteeHealth->Hurt(ExecutionDamage);
			Executee = nullptr;
			ExecuteeHealth = nullptr;
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
			bIsExecuting = false;
			CurrentState = Eps_Walking;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AMoodCharacter: Executee or ExecuteeHealth are invalid."))
		bIsExecuting = false;
		CurrentState = Eps_Walking;
	}
}

void AMoodCharacter::ShootWeapon()
{
	if (CurrentState != Eps_ClimbingLedge && CurrentState != Eps_NoControl)
	{
		WeaponSlotComponent->SetTriggerHeld(true);
	}
}

void AMoodCharacter::StopShootWeapon()
{
	WeaponSlotComponent->SetTriggerHeld(false);
}

void AMoodCharacter::FindLedge()
{
	if (CurrentState == Eps_ClimbingLedge || CurrentState == Eps_NoControl || !bCanClimb)
		return;

	FHitResult BottomHitResult;
	FHitResult TopHitResult;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	const FVector BottomTraceStart = GetActorLocation() + GetActorUpVector() * 40.f;
	const FVector BottomTraceEnd = GetActorLocation() + GetActorForwardVector() * 80.f + GetActorUpVector() * 40.f;

	const FVector TopTraceStart = GetActorLocation() + GetActorUpVector() * 60.f;
	const FVector TopTraceEnd = GetActorLocation() + GetActorForwardVector() * 80.f + GetActorUpVector() * 60.f;

	auto WallInFront = GetWorld()->LineTraceSingleByChannel(BottomHitResult, BottomTraceStart, BottomTraceEnd,
	                                                        ClimbableChannel, QueryParams, FCollisionResponseParams());
	auto WallAbove = GetWorld()->LineTraceSingleByChannel(TopHitResult, TopTraceStart, TopTraceEnd,
	                                                      InterruptClimbingChannel, QueryParams,
	                                                      FCollisionResponseParams());
	if (WallInFront && !WallAbove && bIsMidAir)
	{
		TimeSinceClimbStart = 0.f;
		CurrentState = Eps_ClimbingLedge;

		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = Owner;

		UKismetSystemLibrary::MoveComponentTo(
			RootComponent,
			GetActorLocation() + GetActorForwardVector() * ClimbingLocation.X + GetActorUpVector() * ClimbingLocation.Z,
			/*HitResult.Location, */
			GetActorRotation(),
			true,
			true,
			ClimbingTime,
			false,
			EMoveComponentAction::Move,
			LatentInfo);
	}
}

void AMoodCharacter::KillPlayer(AActor* DeadActor)
{
	bIsDead = true;
	MoodGameMode->ResetMoodValue();
	CurrentState = Eps_NoControl;
}

void AMoodCharacter::RevivePlayer()
{
	HealthComponent->Reset();
}

void AMoodCharacter::DeathCamMovement()
{
	if (bIsDead)
	{
		if (FirstPersonCameraComponent->GetComponentRotation().Roll < 30.f && !bHasRespawned)
		{
			GetController()->SetControlRotation(FMath::Lerp(GetControlRotation(),
			                                                FRotator(GetControlRotation().Pitch,
			                                                         GetControlRotation().Yaw, 40), 0.01));
			AddMovementInput(GetActorForwardVector() * GetWorld()->DeltaTimeSeconds * DeathFallSpeed / 2);
			AddMovementInput(GetActorRightVector() * GetWorld()->DeltaTimeSeconds * DeathFallSpeed / 2);
		}

		if (bHasRespawned)
		{
			if (FirstPersonCameraComponent->GetComponentRotation().Roll > 0)
			{
				GetController()->SetControlRotation(FMath::Lerp(GetControlRotation(),
				                                                FRotator(GetControlRotation().Pitch,
				                                                         GetControlRotation().Yaw, -2), 0.01));
			}

			else
			{
				GetController()->SetControlRotation(FRotator(GetControlRotation().Pitch, GetControlRotation().Yaw,
				                                             0.00f));
				bIsDead = false;
				bHasRespawned = false;
				CurrentState = Eps_Idle;
				RevivePlayer();
			}
		}
	}
}
