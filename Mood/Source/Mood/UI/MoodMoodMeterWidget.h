#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Slate.h"
#include "MoodMoodMeterWidget.generated.h"

class UTextBlock;
class USlider;
class URadialSlider;
class UImage;

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
	UImage* Face;

	virtual void NativeConstruct() override;
	
};
