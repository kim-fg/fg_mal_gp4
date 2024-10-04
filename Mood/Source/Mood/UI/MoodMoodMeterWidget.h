#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodMoodMeterWidget.generated.h"

class UTextBlock;
class USlider;

UCLASS()
class UMoodMoodMeterWidget : public UUserWidget
{
public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	USlider* MoodMeterInnerCircle;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	USlider* MoodMeterMiddleCircle;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	USlider* MoodMeterOuterCircle;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UTextBlock* MoodMeterNumber;
	
};
