#include "MoodLevelSelectWidget.h"
#include "Animation/WidgetAnimation.h"
#include "MoodCyberButton.h"

void UMoodLevelSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();
	LevelSelectButtonLevel1->ButtonClickedSig.AddUniqueDynamic(this, &UMoodLevelSelectWidget::LoadLevelOne);

	CloseLevelSelectButton->ButtonClickedSig.AddUniqueDynamic(this, &UMoodLevelSelectWidget::CloseWidget);
}

void UMoodLevelSelectWidget::OpenWidget_Implementation()
{
	ShowWidget();
}

void UMoodLevelSelectWidget::CloseWidget_Implementation()
{
}

void UMoodLevelSelectWidget::ShowWidget()
{
	this->SetVisibility(ESlateVisibility::Visible);
}

void UMoodLevelSelectWidget::HideWidget()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UMoodLevelSelectWidget::LoadLevelOne()
{
}

