#include "MoodPlayerHealthbar.h"
#include "Components/Progressbar.h"

void UMoodPlayerHealthBar::SetHealthbarPercentage(float NewPercentage)
{
	Healthbar->SetPercent(NewPercentage);
}

void UMoodPlayerHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	/*
	FilledPercentage += InDeltaTime * FillRateMultiplier;
	Healthbar->SetPercent(FilledPercentage);
	*/
}

void UMoodPlayerHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
}
