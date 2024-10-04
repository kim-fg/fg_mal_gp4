#include "MoodMainMenuWidget.h"

#include "MoodGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMoodMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	MoodGameInstance = Cast<UMoodGameInstance>(GetGameInstance());
	StartGameButton->OnClicked.AddUniqueDynamic(this, &UMoodMainMenuWidget::StartGame);
	
}

void UMoodMainMenuWidget::StartGame()
{

	if (MoodGameInstance->Level1 != nullptr)
	{	
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),MoodGameInstance->Level1);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Level 1 reference is missing in the game instance!"));
	}
	
}