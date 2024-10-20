#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodMoodMeterWidget.generated.h"

class UTextBlock;
class USlider;
class URadialSlider;
class UImage;
class UMoodFaceWidget;

UCLASS()
class UMoodMoodMeterWidget : public UUserWidget
{

	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	URadialSlider* MoodMeterInnerCircle;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	URadialSlider* MoodMeterMiddleCircle;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	URadialSlider* MoodMeterOuterCircle;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UTextBlock* MoodMeterNumber;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodFaceWidget* Face;

	UFUNCTION(BlueprintNativeEvent)
	void PlayMoodMeterNumbersAnimation();

	UPROPERTY(BlueprintReadWrite)
	bool AnimationPlaying;

	UPROPERTY(BlueprintReadOnly)
	int AnimationToPlay;

	UPROPERTY(BlueprintReadOnly)
	int PreviousPlayedAnimation;

protected:
	virtual void NativeConstruct() override;
	
};
