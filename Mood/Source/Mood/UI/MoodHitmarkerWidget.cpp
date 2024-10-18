#include "MoodHitmarkerWidget.h"

void UMoodHitmarkerWidget::PlayHitmarkerAnimation_Implementation()
{
	if (!HitmarkerAnimationPlaying)
	{
		this->SetVisibility(ESlateVisibility::HitTestInvisible);
		HitmarkerAnimationPlaying = true;
	}
}

void UMoodHitmarkerWidget::NativeConstruct()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}
