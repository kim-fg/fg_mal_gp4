#include "MoodMainMenuWidget.h"

#include "MoodGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMoodMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	MoodGameInstance = Cast<UMoodGameInstance>(GetGameInstance());
	StartGameButton->OnClicked.AddUniqueDynamic(this, &UMoodMainMenuWidget::StartGame);
	LevelSelectButton->OnClicked.AddDynamic(this, &UMoodMainMenuWidget::LevelSelect);
	
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

void UMoodMainMenuWidget::LevelSelect()
{
	//Extra button press stuff here
}
