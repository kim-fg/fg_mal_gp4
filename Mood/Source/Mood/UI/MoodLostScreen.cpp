#include "MoodLostScreen.h"

#include "MoodGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Mood/MoodGameMode.h"
#include "MoodCyberButton.h"

void UMoodLostScreen::RestartLevel()
{
	GameMode->Respawn();
	//UGameplayStatics::OpenLevel(GetWorld(), FName(GetWorld()->GetName()), false);


}

void UMoodLostScreen::ToMainMenu()
{
	if (MoodGameInstance != nullptr)
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MoodGameInstance->MainMenu, false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Game Instance is nullptr in LostScreen!"));
	}
}

void UMoodLostScreen::RequestBleedoutAnimation_Implementation()
{

}

void UMoodLostScreen::DisplayMenu()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(true);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.f);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void UMoodLostScreen::NativeConstruct()
{
	Super::NativeConstruct();
	
	GameMode = Cast<AMoodGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	MoodGameInstance = Cast<UMoodGameInstance>(GetGameInstance());
	if (RestartButton != nullptr)
	{
		RestartButton->ButtonClickedSig.AddUniqueDynamic(this, &UMoodLostScreen::RestartLevel);
	}
	MainMenuButton->ButtonClickedSig.AddUniqueDynamic(this, &UMoodLostScreen::ToMainMenu);
}
