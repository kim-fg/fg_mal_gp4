#include "MoodCyberButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UMoodCyberButton::OnButtonClicked()
{
	ButtonClickedSig.Broadcast();
}

void UMoodCyberButton::OnButtonHovered()
{
	ButtonHoveredSig.Broadcast();
}

void UMoodCyberButton::OnButtonUnhovered()
{
	ButtonUnhoveredSig.Broadcast();
}

void UMoodCyberButton::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddUniqueDynamic(this, &UMoodCyberButton::OnButtonClicked);
	Button->OnHovered.AddUniqueDynamic(this, &UMoodCyberButton::OnButtonHovered);
	Button->OnUnhovered.AddUniqueDynamic(this, &UMoodCyberButton::OnButtonUnhovered);
	
}

void UMoodCyberButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	ButtonText->SetText(ButtonFText);
	ButtonText->SetColorAndOpacity(TextColor);
}
