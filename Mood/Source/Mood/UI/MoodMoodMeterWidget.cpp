#include "MoodMoodMeterWidget.h"

#include "Components/RadialSlider.h"
#include "Components/TextBlock.h"

void UMoodMoodMeterWidget::PlayMoodMeterNumbersAnimation_Implementation()
{
	if (!AnimationPlaying)
	{
		AnimationToPlay = FMath::RandRange(0, 2);
		AnimationPlaying = true;
	}
}

void UMoodMoodMeterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MoodMeterInnerCircle->SetValue(1.0f);
	MoodMeterInnerCircle->Value = 0.f;
	MoodMeterMiddleCircle->Value = 0.f;
	MoodMeterOuterCircle->Value = 0.f;
	MoodMeterNumber->SetText(FText::FromString("100"));
}
