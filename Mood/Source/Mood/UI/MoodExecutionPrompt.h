#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodExecutionPrompt.generated.h"

class UTextBlock;

UCLASS()
class UMoodExecutionPrompt : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	UTextBlock* ExecutionPrompt;

public:

private:

};