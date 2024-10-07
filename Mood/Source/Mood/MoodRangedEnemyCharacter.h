#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MoodRangedEnemyCharacter.generated.h"

UCLASS()
class MOOD_API AMoodRangedEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UMoodHealthComponent* healthComp;
	
	UPROPERTY(EditAnywhere)
	class UMoodWeaponSlotComponent* WeaponSlotComponent;

	UPROPERTY(EditAnywhere)
	class UMoodWeaponComponent* WeaponComponent;

public:
	// Sets default values for this character's properties
	AMoodRangedEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
