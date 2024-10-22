#include "MoodWinScreen.h"

#include "MoodGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMoodWinScreen::ReturnToMainMenu()
{
	if (MoodGameInstance != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, UGameplayStatics::GetCurrentLevelName(GetWorld(), false));
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, MoodGameInstance->Level1->GetName());
		if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == MoodGameInstance->Level1Name)
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

void UMoodWinScreen::PlayFadeAnimation_Implementation()
{

}

void UMoodWinScreen::NativeConstruct()
{
	Super::NativeConstruct();
	MoodGameInstance = Cast<UMoodGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//MainMenuButton->OnClicked.AddUniqueDynamic(this, &UMoodWinScreen::ReturnToMainMenu);
}
