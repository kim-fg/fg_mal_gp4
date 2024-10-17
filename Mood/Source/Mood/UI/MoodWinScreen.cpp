#include "MoodWinScreen.h"

#include "MoodGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMoodWinScreen::ReturnToMainMenu()
{
	if (MoodGameInstance != nullptr)
	{
		if (UGameplayStatics::GetCurrentLevelName(GetWorld()) != MoodGameInstance->Level1->GetName())
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MoodGameInstance->Level2, false);
		}
		else
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MoodGameInstance->MainMenu, false);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Game Instance is nullptr in WinScreen!"));

	}
}

void UMoodWinScreen::NativeConstruct()
{
	Super::NativeConstruct();
	MoodGameInstance = Cast<UMoodGameInstance>(GetGameInstance());
	MainMenuButton->OnClicked.AddUniqueDynamic(this, &UMoodWinScreen::ReturnToMainMenu);
}
