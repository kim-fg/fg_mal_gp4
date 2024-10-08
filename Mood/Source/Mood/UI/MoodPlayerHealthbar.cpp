#include "MoodPlayerHealthbar.h"
#include "Components/Progressbar.h"

void UMoodPlayerHealthBar::SetHealthbarPercentage(float NewPercentage)
{
	Healthbar->SetPercent(NewPercentage);
}

void UMoodPlayerHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMoodPlayerHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
	if (LeftToRight)
	{
		Healthbar->SetBarFillType(EProgressBarFillType::Type(EProgressBarFillType::LeftToRight));
	}
	else
	{
		Healthbar->SetBarFillType(EProgressBarFillType::Type(EProgressBarFillType::RightToLeft));
	}
}

UMoodPlayerHealthBar::UMoodPlayerHealthBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

