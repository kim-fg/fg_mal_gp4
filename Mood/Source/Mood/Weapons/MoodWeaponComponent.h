// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/SkeletalMeshComponent.h"
#include "MoodWeaponComponent.generated.h"

class ULegacyCameraShake;
class AMoodCharacter;
class UTexture2D;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTrace, FVector, TraceStart, FVector, TraceEnd);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UMoodWeaponComponent : public USkeletalMeshComponent {
    GENERATED_BODY()

public:    
    /** Sets default values for this component's properties */
    UMoodWeaponComponent();
    
    UPROPERTY(BlueprintAssignable)
    FOnTrace OnTrace;

    /** Make the weapon Fire a Projectile */
    UFUNCTION(BlueprintCallable)
    bool Use(FVector MuzzleOrigin, FVector MuzzleDirection, float DamageMultiplier);
    UFUNCTION(BlueprintCallable)
    bool TryAddAmmo(int Amount);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetRange() { return Range; }
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int GetCurrentAmmo() { return CurrentAmmo; }
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UTexture2D* GetAmmoIcon() { return AmmoIcon; }
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UTexture2D* GetCrossHair() { return CrossHair; }
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool HasUnlimitedAmmo() { return UnlimitedAmmo; }
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FString GetAnimationID() { return AnimationID; }
    UFUNCTION(BlueprintCallable, BlueprintPure)
    TSubclassOf<UCameraShakeBase> GetRecoilCameraShake() { return RecoilCameraShake; }

protected:
    virtual void TraceHit(UWorld* World, FVector MuzzleOrigin, FVector MuzzleDirection, float DamageMultiplier);
    
private:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;
    
    UPROPERTY(EditAnywhere, Category=Debug)
    bool DebugBullet = false;

    //todo! MOVE ALL THIS TO A DATA CLASS    
    UPROPERTY(EditDefaultsOnly, Category=Effects)
    USoundBase* FireSound = nullptr;
    UPROPERTY(EditDefaultsOnly, Category=Effects)
    FString AnimationID = "Weapon";
    UPROPERTY(EditDefaultsOnly, Category=Effects)
    TSubclassOf<UCameraShakeBase> RecoilCameraShake = nullptr;
    UPROPERTY(EditDefaultsOnly, Category=Effects)
    TSubclassOf<AActor> HitEffect = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category=Weapon)
    float FireDelay = 0.25f;
    float TimeSinceLastUse = 0;
    
    UPROPERTY(EditDefaultsOnly, Category=Weapon)
    float Range = 10000.0f;
    UPROPERTY(EditDefaultsOnly, Category=Weapon)
    int PelletsPerShot = 5;
    UPROPERTY(EditDefaultsOnly, Category=Weapon)
    int DamagePerPellet = 5;
    UPROPERTY(EditDefaultsOnly, Category=Weapon)
    FVector2f MaxSpread = {0, 0};

    UPROPERTY(EditDefaultsOnly, Category=Weapon)
    bool UnlimitedAmmo = false;
    UPROPERTY(EditDefaultsOnly, Category=Weapon)
    int MaxAmmo = 100;
    UPROPERTY(EditDefaultsOnly, Category=Weapon)
    int StartAmmo = 25;
    int CurrentAmmo = 0;

    UPROPERTY(EditDefaultsOnly, Category=UI)
    UTexture2D* AmmoIcon = nullptr;
    UPROPERTY(EditDefaultsOnly, Category=UI)
    UTexture2D* CrossHair = nullptr;
};
