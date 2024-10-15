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
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UMoodPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->ButtonClickedSig.AddUniqueDynamic(this, &UMoodPauseMenu::ResumeGame);
	OpenOptionsMenuButton->ButtonClickedSig.AddUniqueDynamic(this, &UMoodPauseMenu::OpenOptionsMenu);
}
