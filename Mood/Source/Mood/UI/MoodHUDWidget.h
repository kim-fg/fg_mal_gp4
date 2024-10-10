#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodHUDWidget.generated.h"


class UMoodWeaponComponent;
class UMoodAmmoWidget;
class UMoodMoodMeterWidget;
class UMoodWinScreen;
class UMoodLostScreen;
class UMoodPlayerHealthBar;
class UMoodHealthComponent;
class AMoodGameMode;
class UMoodWeaponSlotComponent;
struct FInputModeUIOnly;

UCLASS()

class UMoodHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
#pragma region Widgets

	UPROPERTY(meta = (BindWidget))
	UMoodPlayerHealthBar* HealthBarRight;

	UPROPERTY(meta = (BindWidget))
	UMoodPlayerHealthBar* HealthBarLeft;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodLostScreen* LostScreen;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodWinScreen* WinScreen;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodMoodMeterWidget* MoodMeterWidget;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodAmmoWidget* AmmoWidget;

#pragma endregion


#pragma region Component Variables

	UPROPERTY()
	UMoodHealthComponent* HealthComponent;
	UPROPERTY()
	UMoodWeaponSlotComponent* WeaponSlotComponent;
	UPROPERTY()
	UMoodWeaponComponent* Weapon;

#pragma endregion

	//Manager Variables
	UPROPERTY()
	AMoodGameMode* GameMode;


	//Spin radial variables
	UPROPERTY()
	float InnerCircleSpin = 0.3f;
	UPROPERTY()
	float MiddleCircleSpin = 0.2f;
	UPROPERTY()
	float OuterCircleSpin = 0.1f;
	//text change variable
	UPROPERTY()
	int MoodMeterNumber;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

#pragma region Component Functions

	void GetHealthComponent(ACharacter* Player);
	void GetWeaponSlotComponent(ACharacter* Player);

#pragma endregion

#pragma region Update Widgets

	void UpdateHealthbarWidget();
	void UpdateAmmoWidget();
	void UpdateMoodMeterWidget(const FGeometry& MyGeometry, float InDeltaTime);
	void UpdateMoodMeterBars(const FGeometry& MyGeometry, float InDeltaTime, float MoodMeterValue);
	void UpdateCrosshair();

#pragma endregion


	UFUNCTION(Blueprintable)
	void DisplayLostScreen();

	UFUNCTION(Blueprintable)
	void DisplayWinScreen();

	UFUNCTION(Blueprintable)
	void HideLostScreen();

	virtual void NativeConstruct() override;

	
};
