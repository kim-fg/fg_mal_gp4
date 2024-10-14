#include "MoodPauseMenu.h"
#include "Components/Button.h"
#include "MoodCyberButton.h"
#include "MoodOptionsMenuWidget.h"
#include "Kismet/GameplayStatics.h"

void UMoodPauseMenu::OpenOptionsMenu_Implementation()
{
	OptionsMenuWidget->OpenWidget();
}

void UMoodPauseMenu::ResumeGame_Implementation()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}

void UMoodPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	OpenOptionsMenuButton->ButtonClickedSig.AddUniqueDynamic(this, &UMoodPauseMenu::OpenOptionsMenu);
}
