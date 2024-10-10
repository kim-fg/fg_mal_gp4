#include "MoodWeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Mood/MoodHealthComponent.h"

// Sets default values for this component's properties
/**
 * 
 */
UMoodWeaponComponent::UMoodWeaponComponent(): USkeletalMeshComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

bool UMoodWeaponComponent::TryAddAmmo(int Amount) {
	if (CurrentAmmo == MaxAmmo) { return false; }
	
	Amount = abs(Amount);
	CurrentAmmo += Amount;
	if (CurrentAmmo > MaxAmmo) {
		CurrentAmmo = MaxAmmo;
	}

	return true;
}

void UMoodWeaponComponent::TraceHit(UWorld* World, FVector MuzzleOrigin, FVector MuzzleDirection, float DamageMultiplier) {
	auto LineTraceEnd = MuzzleOrigin + MuzzleDirection * Range;
	FHitResult Hit {};
	FCollisionQueryParams CollisionQueryParams{};
	CollisionQueryParams.AddIgnoredActor(GetAttachmentRootActor());
	World->LineTraceSingleByChannel(Hit, MuzzleOrigin, LineTraceEnd, ECC_Visibility, CollisionQueryParams);

	if (DebugBullet) {
		DrawDebugLine(
			World, MuzzleOrigin, LineTraceEnd, FColor::Green,
			false, 0.25f, 0, 0.25f
		);
	}
	
	if (Hit.IsValidBlockingHit()) {
		auto HitActor = Hit.GetActor();
		if (HitActor) {
			auto Health = HitActor->GetComponentByClass<UMoodHealthComponent>();
			if (Health) {
				auto ActualDamage = FMath::FloorToInt32(DamagePerPellet * DamageMultiplier);
				Health->Hurt(ActualDamage);
				if (DebugBullet) {
					UE_LOG(LogTemp, Log, TEXT("Shot %ls"), *Hit.GetActor()->GetActorNameOrLabel());
				}
			}
		}

		if (HitEffect) {
			GetWorld()->SpawnActor(HitEffect, &Hit.Location, &FRotator::ZeroRotator); 
		}
	}
}

bool UMoodWeaponComponent::Use(FVector MuzzleOrigin, FVector MuzzleDirection, float DamageMultiplier) {
	if (!UnlimitedAmmo && CurrentAmmo < 1) {
		return false;
	}
	
	if (TimeSinceLastUse < FireDelay) {
		return false;
	}

	// Reset this now that we've fired the shot
	TimeSinceLastUse = 0.0f;
	// Use up ammo
	if (!UnlimitedAmmo) {
		CurrentAmmo--;
	}
	
	UWorld* const World = GetWorld();
	if (World != nullptr) {
		for (auto i = 0; i < PelletsPerShot; i++) {
			auto Spread = FVector(
				FMath::FRandRange(-MaxSpread.X, MaxSpread.X),
				0.0f,
				FMath::FRandRange(-MaxSpread.Y, MaxSpread.Y)
			);

			TraceHit(World, MuzzleOrigin, MuzzleDirection + Spread, DamageMultiplier);
		}
	}

	// Try and play the sound if specified
	if (FireSound != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, MuzzleOrigin);
	}
	
	return true;
}

void UMoodWeaponComponent::BeginPlay() {
	Super::BeginPlay();

	TimeSinceLastUse = FireDelay;
	CurrentAmmo = StartAmmo;
}

void UMoodWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastUse += DeltaTime;
}
