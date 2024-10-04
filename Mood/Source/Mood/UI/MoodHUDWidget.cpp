#include "MoodHUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/MoodCharacter.h"
#include "../MoodHealthComponent.h"
#include "MoodLostScreen.h"
#include "MoodPlayerHealthbar.h"
#include "MoodWinScreen.h"
#include "Components/ProgressBar.h"

void UMoodHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (HealthComponent != nullptr)
	{
		HealthBar->Healthbar->SetPercent(HealthComponent->HealthPercent());	
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("HealthComponent is nullptr in the HUD!"));
	}
}

void UMoodHUDWidget::GetHealthComponent()
{
	HealthComponent = UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->FindComponentByClass<UMoodHealthComponent>();
}

void UMoodHUDWidget::DisplayLostScreen()
{
	LostScreen->SetVisibility(ESlateVisibility::Visible);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(true);
	
}


void UMoodHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (UGameplayStatics::GetPlayerCharacter(GetWorld(),0) != nullptr)
	{
		GetHealthComponent();
	}
	HealthComponent->OnDeath.AddUniqueDynamic(this, &UMoodHUDWidget::DisplayLostScreen);
	LostScreen->SetVisibility(ESlateVisibility::Hidden);
	WinScreen->SetVisibility(ESlateVisibility::Hidden);
}

