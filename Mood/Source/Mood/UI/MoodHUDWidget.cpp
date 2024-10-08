#include "MoodHUDWidget.h"
#include "MoodHUDWidget.h"

#include <string>

#include "Kismet/GameplayStatics.h"
#include "../Player/MoodCharacter.h"
#include "../MoodHealthComponent.h"
#include "../Weapons/MoodWeaponSlotComponent.h"
#include "../Weapons/MoodWeaponComponent.h"
#include "MoodLostScreen.h"
#include "MoodMoodMeterWidget.h"
#include "MoodPlayerHealthbar.h"
#include "MoodAmmoWidget.h"
#include "MoodWinScreen.h"
#include "Components/RadialSlider.h"
#include "Components/ProgressBar.h"
#include "../MoodGameMode.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMoodHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//Setting Healthbar values
	if (HealthComponent != nullptr)
	{
		HealthBarRight->Healthbar->SetPercent(HealthComponent->HealthPercent());
		HealthBarLeft->Healthbar->SetPercent(HealthComponent->HealthPercent());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("HealthComponent is nullptr in the HUD!"));
	}
	
	//Ammo counter update
	if (WeaponSlotComponent != nullptr)
	{
		Weapon = WeaponSlotComponent->GetSelectedWeapon();
		if (Weapon != nullptr)
		{
			AmmoWidget->AmmoText->SetText(FText::FromString(FString::FromInt(Weapon->GetCurrentAmmo())));
			AmmoWidget->AmmoIcon->SetBrushFromTexture(Weapon->GetAmmoIcon());
		}
	}

	
	
	//Spinning radial + counting text
	InnerCircleSpin += InDeltaTime / 10;
	MiddleCircleSpin += InDeltaTime / 10;
	OuterCircleSpin += InDeltaTime / 10;
	MoodMeterNumber += InDeltaTime * 100;
	FString FloatyString = FString::SanitizeFloat(InDeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Yellow, *FloatyString);
	MoodMeterWidget->MoodMeterInnerCircle->SetValue(InnerCircleSpin);
	MoodMeterWidget->MoodMeterMiddleCircle->SetValue(MiddleCircleSpin);
	MoodMeterWidget->MoodMeterOuterCircle->SetValue(OuterCircleSpin);
	if (InnerCircleSpin >= 1.0f)
		InnerCircleSpin = 0.f;
	if (MiddleCircleSpin >= 1.0f)
		MiddleCircleSpin = 0.f;
	if (OuterCircleSpin >= 1.0f)
		OuterCircleSpin = 0.f;
	FString FormattedInt = FString::FormatAsNumber(MoodMeterNumber);
	MoodMeterWidget->MoodMeterNumber->SetText(FText::FromString(FormattedInt));
	
	if (MoodMeterNumber >= 666)
		MoodMeterNumber = 0;

	
		
}

void UMoodHUDWidget::GetHealthComponent(ACharacter* Player)
{
	HealthComponent = Player->FindComponentByClass<UMoodHealthComponent>();
}

void UMoodHUDWidget::GetWeaponSlotComponent(ACharacter* Player)
{
	WeaponSlotComponent = Player->FindComponentByClass<UMoodWeaponSlotComponent>();
}

void UMoodHUDWidget::UpdateAmmo()
{

}

void UMoodHUDWidget::DisplayLostScreen()
{
	LostScreen->SetVisibility(ESlateVisibility::Visible);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(true);
	
}

void UMoodHUDWidget::DisplayWinScreen()
{
	WinScreen->SetVisibility(ESlateVisibility::Visible);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(true);
}


void UMoodHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) != nullptr)
	{
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		GetHealthComponent(Player);
		GetWeaponSlotComponent(Player);
	}
	
	HealthComponent->OnDeath.AddUniqueDynamic(this, &UMoodHUDWidget::DisplayLostScreen);
	GameMode = Cast<AMoodGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->GameFinishedSig.AddUniqueDynamic(this, &UMoodHUDWidget::DisplayWinScreen);
	LostScreen->SetVisibility(ESlateVisibility::Hidden);
	WinScreen->SetVisibility(ESlateVisibility::Hidden);
	MoodMeterWidget->MoodMeterInnerCircle->SetValue(InnerCircleSpin);
	MoodMeterWidget->MoodMeterMiddleCircle->SetValue(MiddleCircleSpin);
	MoodMeterWidget->MoodMeterOuterCircle->SetValue(OuterCircleSpin);

}

