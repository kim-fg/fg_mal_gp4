#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player/MoodCharacter.h"
#include "MoodMeleeEnemyCharacter.generated.h"

UCLASS()
class MOOD_API AMoodMeleeEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* attackradius;

	UPROPERTY(EditAnywhere)
	class UMoodHealthComponent* healthComp;

	UPROPERTY(EditAnywhere)
	class UMoodWeaponSlotComponent* WeaponSlotComponent;

public:

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Sets default values for this character's properties
	AMoodMeleeEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
private:

	
};
