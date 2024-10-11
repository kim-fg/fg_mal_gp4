#include "MoodLevelSelectWidget.h"
#include "Animation/WidgetAnimation.h"
#include "MoodGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MoodCyberButton.h"

void UMoodLevelSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();
	this->SetVisibility(ESlateVisibility::Hidden);
	LevelSelectButtonLevel1->ButtonClickedSig.AddUniqueDynamic(this, &UMoodLevelSelectWidget::LoadLevelOne);
	LevelSelectButtonLevel2->ButtonClickedSig.AddUniqueDynamic(this, &UMoodLevelSelectWidget::LoadLevelTwo);
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
	this->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UMoodLevelSelectWidget::HideWidget()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UMoodLevelSelectWidget::LoadLevelOne()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), Cast<UMoodGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())));
}

void UMoodLevelSelectWidget::LoadLevelTwo()
{

}

