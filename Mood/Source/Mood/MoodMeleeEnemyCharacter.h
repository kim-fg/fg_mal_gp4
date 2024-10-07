#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MoodMeleeEnemyCharacter.generated.h"

UCLASS()
class MOOD_API AMoodMeleeEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UMoodHealthComponent* healthComp;

public:
	// Sets default values for this character's properties
	AMoodMeleeEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
