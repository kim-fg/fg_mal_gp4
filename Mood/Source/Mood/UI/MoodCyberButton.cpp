#include "MoodCyberButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UMoodCyberButton::OnButtonClicked()
{
	ButtonClickedSig.Broadcast();
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClicked);
}

void UMoodCyberButton::OnButtonHovered()
{
	ButtonHoveredSig.Broadcast();
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonHovered);
}

void UMoodCyberButton::OnButtonUnhovered()
{
	ButtonUnhoveredSig.Broadcast();
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonHovered);
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
