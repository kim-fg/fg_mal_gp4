#include "MoodMoodStage.h"

void UMoodMoodStage::PlayStageAnimation_Implementation()
{
	this->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UMoodMoodStage::NativeConstruct()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}
