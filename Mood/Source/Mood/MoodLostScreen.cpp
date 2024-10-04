#include "MoodLostScreen.h"

#include "MoodGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMoodLostScreen::RestartLevel()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), this, false);
}

void UMoodLostScreen::ToMainMenu()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MoodGameInstance->MainMenu, false);
}

void UMoodLostScreen::NativeConstruct()
{
	Super::NativeConstruct();
	MoodGameInstance = Cast<UMoodGameInstance>(GetGameInstance());
	RestartButton->OnClicked.AddUniqueDynamic(this, &UMoodLostScreen::RestartLevel);
	MainMenuButton->OnClicked.AddUniqueDynamic(this, &UMoodLostScreen::ToMainMenu);
}
