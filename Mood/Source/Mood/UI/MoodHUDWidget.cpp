#include "MoodHUDWidget.h"

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
#include "Kismet/KismetMathLibrary.h"
#include "MoodPauseMenu.h"
#include "MoodFaceWidget.h"
#include "MoodMoodStage.h"
#include "Components/RetainerBox.h"
#include "MoodHitmarkerWidget.h"

void UMoodHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//Updating Widget Elements
	UpdateHealthbarWidget();
	UpdateAmmoWidget();
	UpdateMoodMeterWidget(MyGeometry, InDeltaTime);
	UpdateHUDTint();
	PlayGlitchEffect(MyGeometry, InDeltaTime);
}

void UMoodHUDWidget::GetHealthComponent(ACharacter* PlayerPass)
{
	HealthComponent = PlayerPass->FindComponentByClass<UMoodHealthComponent>();
}

void UMoodHUDWidget::GetWeaponSlotComponent(ACharacter* PlayerPass)
{
	WeaponSlotComponent = PlayerPass->FindComponentByClass<UMoodWeaponSlotComponent>();
}

void UMoodHUDWidget::UpdateHealthbarWidget()
{
	if (HealthComponent != nullptr)
	{
		HealthBarRight->Healthbar->SetPercent(HealthComponent->HealthPercent());
		HealthBarLeft->Healthbar->SetPercent(HealthComponent->HealthPercent());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("HealthComponent is nullptr in the HUD!"));
	}
}

void UMoodHUDWidget::UpdateAmmoWidget()
{
	if (WeaponSlotComponent != nullptr)
	{
		Weapon = WeaponSlotComponent->GetSelectedWeapon();
		UpdateCrosshair(Weapon);
		if (Weapon != nullptr)
		{
			if (Weapon->HasUnlimitedAmmo())
			{
				//THIS SUCKS
				AmmoWidget->AmmoTextInfinite->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				AmmoWidget->AmmoText->SetText(FText::FromString(""));
			}
			else
			{
				//I HATE THIS
				AmmoWidget->AmmoTextInfinite->SetVisibility(ESlateVisibility::Hidden);
				AmmoWidget->AmmoText->SetText(FText::FromString(FString::FromInt(Weapon->GetCurrentAmmo())));
			}
			AmmoWidget->AmmoIcon->SetBrushFromTexture(Weapon->GetAmmoIcon());
		}
		else
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("WeaponComponent is nullptr in the HUD!"));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("WeaponSlotComponent is nullptr in the HUD!"));
}

void UMoodHUDWidget::UpdateMoodMeterWidget(const FGeometry& MyGeometry, float InDeltaTime)
{
	MoodMeterValue = GameMode->GetMoodMeterValue();
	MoodMeterValue = FMath::Clamp(MoodMeterValue, 0.f, 666.f);
	MoodMeterWidget->MoodMeterNumber->SetText(FText::FromString(FString::FromInt(FMath::FloorToInt32(MoodMeterValue))));

	UpdateMoodMeterBars(MyGeometry, InDeltaTime, MoodMeterValue);
}

void UMoodHUDWidget::UpdateMoodMeterBars(const FGeometry& MyGeometry, float InDeltaTime, float MoodMeterValueToText)
{
	if (MoodMeterValueToText >= 0 && MoodMeterValueToText <= 222)
	{
		MoodMeterWidget->MoodMeterMiddleCircle->SetValue(0.f);
		MoodMeterWidget->MoodMeterOuterCircle->SetValue(0.f);
		MoodMeterValueToText = UKismetMathLibrary::NormalizeToRange(MoodMeterValueToText, 0, 222);
		MoodMeterWidget->MoodMeterInnerCircle->SetValue(MoodMeterValueToText);
	}
	else if (MoodMeterValueToText >= 223 && MoodMeterValueToText <= 444)
	{
		MoodMeterWidget->MoodMeterInnerCircle->SetValue(1.f);
		MoodMeterWidget->MoodMeterOuterCircle->SetValue(0.f);
		MoodMeterValueToText = UKismetMathLibrary::NormalizeToRange(MoodMeterValueToText, 223, 444);
		MoodMeterWidget->MoodMeterMiddleCircle->SetValue(MoodMeterValueToText);
	}
	else if (MoodMeterValueToText >= 445 && MoodMeterValueToText <= 666)
	{
		MoodMeterWidget->MoodMeterInnerCircle->SetValue(1.f);
		MoodMeterWidget->MoodMeterMiddleCircle->SetValue(1.f);
		MoodMeterValueToText = UKismetMathLibrary::NormalizeToRange(MoodMeterValueToText, 445, 666);
		MoodMeterWidget->MoodMeterOuterCircle->SetValue(MoodMeterValueToText);
	}
}

void UMoodHUDWidget::UpdateCrosshair(UMoodWeaponComponent* WeaponToPass)
{
	CrossHair->SetBrushFromTexture(Weapon->GetCrossHair(), false);
}

void UMoodHUDWidget::UpdateHUDTint()
{
	switch (GameMode->GetMoodState())
	{
	case EMoodState::Ems_NoMood:
		SetTint(TintColorStage0, TintColorStage0);
		break;
	case EMoodState::Ems_Mood222:
		SetTint(TintColorStage1, TintColorStage1);
		break;
	case EMoodState::Ems_Mood444:
		SetTint(TintColorStage2, TintColorStage1);
		break;
	case EMoodState::Ems_Mood666:
		SetTint(TintColorStage3, TintColorStage3);
		break;
	default:
		break;
	}
}

void UMoodHUDWidget::SetTint(FLinearColor Color, FLinearColor FaceColor)
{
	MoodMeterWidget->MoodMeterInnerCircle->SetSliderProgressColor(Color);
	MoodMeterWidget->MoodMeterMiddleCircle->SetSliderProgressColor(Color);
	MoodMeterWidget->MoodMeterOuterCircle->SetSliderProgressColor(Color);
	MoodMeterWidget->MoodMeterNumber->SetColorAndOpacity(Color);
	MoodMeterWidget->Face->SetColorAndOpacity(FaceColor);
	AmmoWidget->SetColorAndOpacity(Color);
	BottomRightCorner->SetColorAndOpacity(Color);
	BottomLeftCorner->SetColorAndOpacity(Color);
	TopLeftCorner->SetColorAndOpacity(Color);
	TopRightCorner->SetColorAndOpacity(Color);
}

void UMoodHUDWidget::PlayGlitchEffect(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (GlitchHurtPlaying)
	{
		GlitchHurtTimer += InDeltaTime;
		GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Red, FString::SanitizeFloat(GlitchHurtTimer));
		if (GlitchHurtTimer <= 0.25f)
		{
			if (!GlitchEffectSet)
			{
				GlitchEffectWidget->SetEffectMaterial(M_GlitchEffectEnabled);
				GlitchEffectWidget->SetTextureParameter("GlitchUI");
				GlitchEffectSet = true;
			}
		}
		else
		{
			GlitchEffectWidget->SetEffectMaterial(M_GlitchEffectDisabled);
			GlitchEffectWidget->SetTextureParameter("GlitchUI");
			GlitchHurtPlaying = false;
			GlitchHurtTimer = 0.f;
			GlitchEffectSet = false;
		}
	}
}

void UMoodHUDWidget::RequestHurtAnimation(int Amount, int NewHealth)
{
	if (MoodMeterValue < 666.f)
	MoodMeterWidget->Face->PlayHurtAnimation();
	if (!GlitchHurtPlaying)
	{
		GlitchHurtPlaying = true;
	}
}

void UMoodHUDWidget::RequestStageAdvanceAnimation(EMoodState IncomingState)
{
	switch (IncomingState)
	{
	case Ems_Mood222:
		MoodStage222Widget->PlayStageAnimation();
		break;
	case Ems_Mood444:
		MoodStage444Widget->PlayStageAnimation();
		break;
	case Ems_Mood666:
		MoodStage666Widget->PlayStageAnimation();
		break;
	default:
		break;
	}
}

void UMoodHUDWidget::RequestHitmarkerAnimation()
{
	HitmarkerWidget->PlayHitmarkerAnimation();
}

void UMoodHUDWidget::RequestMoodMeterValueAnimation()
{
	MoodMeterWidget->PlayMoodMeterNumbersAnimation();
}

void UMoodHUDWidget::DisplayLostScreen(AActor* DeadActor)
{
	LostScreen->SetVisibility(ESlateVisibility::Visible);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(true);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.f);
	UGameplayStatics::SetGamePaused(GetWorld(),true);
}

void UMoodHUDWidget::DisplayWinScreen()
{
	WinScreen->SetVisibility(ESlateVisibility::Visible);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->SetShowMouseCursor(true);
}

void UMoodHUDWidget::HideLostScreen()
{
	LostScreen->SetVisibility(ESlateVisibility::Hidden);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	UGameplayStatics::SetGamePaused(GetWorld(),false);
}

void UMoodHUDWidget::DisplayPauseMenu()
{
	if (!UGameplayStatics::IsGamePaused(GetWorld()))
	{
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->SetShowMouseCursor(true);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.f);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}


void UMoodHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Player = Cast<AMoodCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player != nullptr)
	{
		GetHealthComponent(Player);
		GetWeaponSlotComponent(Player);
	}
	
	HealthComponent->OnDeath.AddUniqueDynamic(this, &UMoodHUDWidget::DisplayLostScreen);
	GameMode = Cast<AMoodGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->GameFinishedSig.AddUniqueDynamic(this, &UMoodHUDWidget::DisplayWinScreen);
	GameMode->PlayerRespawn.AddUniqueDynamic(this, &UMoodHUDWidget::HideLostScreen);
	LostScreen->SetVisibility(ESlateVisibility::Hidden);
	WinScreen->SetVisibility(ESlateVisibility::Hidden);
	PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	MoodMeterWidget->MoodMeterInnerCircle->SetValue(0);
	MoodMeterWidget->MoodMeterMiddleCircle->SetValue(0);
	MoodMeterWidget->MoodMeterOuterCircle->SetValue(0);
	GameMode->OnEnemyHit.AddUniqueDynamic(this, &UMoodHUDWidget::RequestHitmarkerAnimation);
	GameMode->OnEnemyHit.AddUniqueDynamic(this, &UMoodHUDWidget::RequestMoodMeterValueAnimation);
	Player->OnPaused.AddUniqueDynamic(this, &UMoodHUDWidget::DisplayPauseMenu);
	HealthComponent->OnHurt.AddUniqueDynamic(this, &UMoodHUDWidget::RequestHurtAnimation);
	GameMode->OnSlowMotionTriggered.AddUniqueDynamic(this, &UMoodHUDWidget::RequestStageAdvanceAnimation);
}

