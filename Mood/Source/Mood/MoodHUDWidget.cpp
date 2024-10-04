#include "MoodHUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MoodCharacter.h"
#include "MoodHealthComponent.h"
#include "MoodPlayerHealthbar.h"
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

bool UMoodHUDWidget::Initialize()
{
	return Super::Initialize();
}

void UMoodHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (UGameplayStatics::GetPlayerCharacter(GetWorld(),0) != nullptr)
	{
		GetHealthComponent();
	}
}

