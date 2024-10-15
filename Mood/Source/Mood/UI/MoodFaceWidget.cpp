#include "MoodFaceWidget.h"

#include "Components/Image.h"

void UMoodFaceWidget::PlayHurtAnimation_Implementation()
{
	if (HurtAnimationIsPlaying)
		return;
}

void UMoodFaceWidget::PlayLaughingAnimation_Implementation()
{
	
}

void UMoodFaceWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (IsMoodMeterUI)
	{
		HPFace1->SetRenderOpacity(1.f);
		HPFace2->SetRenderOpacity(0.f);
		HPFace3->SetRenderOpacity(0.f);
		HPFace4->SetRenderOpacity(0.f);
		HPFace5->SetRenderOpacity(0.f);
		Face666One->SetRenderOpacity(0.f);
		Face666One->SetRenderOpacity(0.f);
		Face666One->SetVisibility(ESlateVisibility::Hidden);
		Face666Two->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		HPFace1->SetVisibility(ESlateVisibility::Hidden);
		HPFace2->SetVisibility(ESlateVisibility::Hidden);
		HPFace3->SetVisibility(ESlateVisibility::Hidden);
		HPFace4->SetVisibility(ESlateVisibility::Hidden);
		HPFace5->SetVisibility(ESlateVisibility::Hidden);
		HPFace1->SetRenderOpacity(0.f);
		HPFace2->SetRenderOpacity(0.f);
		HPFace3->SetRenderOpacity(0.f);
		HPFace4->SetRenderOpacity(0.f);
		HPFace5->SetRenderOpacity(0.f);
		Face666One->SetRenderOpacity(1.f);
		Face666One->SetRenderOpacity(0.f);
	}
}
