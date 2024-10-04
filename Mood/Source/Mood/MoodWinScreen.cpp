#include "MoodWinScreen.h"

#include "MoodGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMoodWinScreen::ReturnToMainMenu()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MoodGameInstance->MainMenu, false);
}

void UMoodWinScreen::NativeConstruct()
{
	Super::NativeConstruct();
	MoodGameInstance = Cast<UMoodGameInstance>(GetGameInstance());
	MainMenuButton->OnClicked.AddUniqueDynamic(this, &UMoodWinScreen::ReturnToMainMenu);
}
