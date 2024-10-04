#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MoodRangedEnemyAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UBehaviorTree;

UCLASS()
class MOOD_API AMoodRangedEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMoodRangedEnemyAIController(); 

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	// behaviour tree
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent { nullptr };

	// blackboard component, uses the blackboard owned by the behavior tree
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

private:
	UPROPERTY()
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
};