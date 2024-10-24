#include "MoodPauseMenu.h"
#include "MoodCyberButton.h"
#include "MoodOptionsMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../MoodHealthComponent.h"

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

void UMoodPauseMenu::RestartLevel()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	Super::RestartLevel();
}

void UMoodPauseMenu::FullResetLevel()
{
	FName Level = FName(UGameplayStatics::GetCurrentLevelName(GetWorld(), true));
	UGameplayStatics::OpenLevel(GetWorld(), Level, true);
}

void UMoodPauseMenu::PassHealthComponent(UMoodHealthComponent* PassHealthComp)
{
	PlayerHealth = PassHealthComp;
}

void UMoodPauseMenu::KillPlayerInPause()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	PlayerHealth->Hurt(10000000);
}

void UMoodPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	ResumeButton->ButtonClickedSig.AddUniqueDynamic(this, &UMoodPauseMenu::ResumeGame);
	OpenOptionsMenuButton->ButtonClickedSig.AddUniqueDynamic(this, &UMoodPauseMenu::OpenOptionsMenu);
	ResetLevelButton->ButtonClickedSig.AddUniqueDynamic(this, &UMoodPauseMenu::FullResetLevel);
	KillPlayerButton->ButtonClickedSig.AddUniqueDynamic(this, &UMoodPauseMenu::KillPlayerInPause);
}
