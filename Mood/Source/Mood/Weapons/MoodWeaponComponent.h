// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/SkeletalMeshComponent.h"
#include "MoodWeaponComponent.generated.h"

class ULegacyCameraShake;
class AMoodCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UMoodWeaponComponent : public USkeletalMeshComponent {
    GENERATED_BODY()

public:    
    /** Sets default values for this component's properties */
    UMoodWeaponComponent();
    
    /** Make the weapon Fire a Projectile */
    UFUNCTION(BlueprintCallable, Category="Weapon")
    bool Use(FVector MuzzleOrigin, FVector MuzzleDirection);

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

    float GetRange() { return Range; }

    UFUNCTION(BlueprintCallable, BlueprintPure)
    FString GetAnimationID() { return AnimationID; }

    TSubclassOf<UCameraShakeBase> GetRecoilCameraShake() { return RecoilCameraShake; }

protected:
    virtual void TraceHit(UWorld* World, FVector MuzzleOrigin, FVector MuzzleDirection);
    
private:
    UPROPERTY(EditDefaultsOnly, Category=Effects)
    USoundBase* FireSound;
    UPROPERTY(EditDefaultsOnly, Category=Effects)
    float Recoil = 1.0f;
    UPROPERTY(EditDefaultsOnly, Category=Effects)
    FString AnimationID;
    UPROPERTY(EditDefaultsOnly, Category=Effects)
    TSubclassOf<UCameraShakeBase> RecoilCameraShake;
    
    UPROPERTY(EditDefaultsOnly)
    float FireDelay = 0.25f;
    UPROPERTY(EditDefaultsOnly)
    float Range = 10000.0f;
    UPROPERTY(EditDefaultsOnly)
    int PelletsPerShot = 5;
    UPROPERTY(EditDefaultsOnly)
    int DamagePerPellet = 5;
    UPROPERTY(EditDefaultsOnly)
    FVector2f MaxSpread = {0, 0};

    float TimeSinceLastUse;
};
