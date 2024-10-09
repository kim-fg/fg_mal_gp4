#include "MoodMainMenuWidget.h"

#include "MoodGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMoodMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	MoodGameInstance = Cast<UMoodGameInstance>(GetGameInstance());
	StartGameButton->OnClicked.AddUniqueDynamic(this, &UMoodMainMenuWidget::StartGame);
	LevelSelectButton->OnClicked.AddUniqueDynamic(this, &UMoodMainMenuWidget::ShowLevelSelectMenu);
	OptionsButton->OnClicked.AddUniqueDynamic(this, &UMoodMainMenuWidget::ShowOptionsMenu);
	ExitGameButton->OnClicked.AddUniqueDynamic(this, &UMoodMainMenuWidget::ExitGame);
	
}

void UMoodMainMenuWidget::StartGame()
{

	if (MoodGameInstance != nullptr)
	{	
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),MoodGameInstance->Level1);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Game Instance is nullptr in MainMenuWidget!"));
	}
	
}

void UMoodMainMenuWidget::ShowLevelSelectMenu()
{
	
}

void UMoodMainMenuWidget::ShowOptionsMenu()
{
	
}

void UMoodMainMenuWidget::ExitGame()
{
	//FGenericPlatformMisc::RequestExit(false);
	UKismetSystemLibrary::QuitGame(GetWorld(),UGameplayStatics::GetPlayerController(GetWorld(), 0),EQuitPreference::Quit,true);
}
