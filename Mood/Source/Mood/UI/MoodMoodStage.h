#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodMoodStage.generated.h"

class UImage;

UCLASS()
class UMoodMoodStage : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite);
	UImage* Face;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite);
	UImage* Face2;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite);
	UImage* StageNumber;

protected:

	
	
private:


};