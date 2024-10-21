#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Weapons/MoodWeaponComponent.h"
#include "MoodHUDWidget.generated.h"


class URetainerBox;
class UMoodWeaponComponent;
class UMoodAmmoWidget;
class UMoodMoodMeterWidget;
class UMoodWinScreen;
class UMoodLostScreen;
class UMoodPlayerHealthBar;
class UMoodHealthComponent;
class AMoodGameMode;
class UImage;
class UMoodWeaponSlotComponent;
class UMoodPauseMenu;
class UMoodMoodStage;
class UMaterialInstance;
class UMoodHitmarkerWidget;
class UMoodWeaponSlotWidget;
struct FInputModeUIOnly;
enum EMoodState;

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

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodPauseMenu* PauseMenu;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UImage* CrossHair;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UImage* BottomRightCorner;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UImage* BottomLeftCorner;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UImage* TopLeftCorner;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UImage* TopRightCorner;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodMoodStage* MoodStage222Widget;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodMoodStage* MoodStage444Widget;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodMoodStage* MoodStage666Widget;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	URetainerBox* GlitchEffectWidget;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodHitmarkerWidget* HitmarkerWidget;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodWeaponSlotWidget* WeaponSlotWidget;

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

	UPROPERTY(EditDefaultsOnly)
	FLinearColor TintColorStage0;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor TintColorStage1;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor TintColorStage2;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor TintColorStage3;


	UPROPERTY()
	AMoodCharacter* Player = nullptr;

	//text change variable
	UPROPERTY()
	float MoodMeterValue;

	UPROPERTY()
	bool GlitchHurtPlaying = false;

	UPROPERTY()
	float GlitchHurtTimer = 0.f;

	UPROPERTY()
	bool GlitchEffectSet = false;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* M_GlitchEffectEnabled;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* M_GlitchEffectDisabled;

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
	void UpdateCrosshair(UMoodWeaponComponent* WeaponToPass);
	void UpdateHUDTint();
	void SetTint(FLinearColor Color, FLinearColor FaceColor);
	void PlayGlitchEffect(const FGeometry& MyGeometry, float InDeltaTime);

#pragma endregion


	UFUNCTION(Blueprintable)
	void DisplayLostScreen(AActor* DeadActor);

	UFUNCTION(Blueprintable)
	void DisplayWinScreen();

	UFUNCTION(Blueprintable)
	void HideLostScreen();

	UFUNCTION(Blueprintable)
	void DisplayPauseMenu();

	UFUNCTION()
	void RequestHurtAnimation(int Amount, int NewHealth);

	UFUNCTION()
	void RequestStageAdvanceAnimation(EMoodState IncomingState);

	UFUNCTION()
	void RequestHitmarkerAnimation();

	UFUNCTION()
	void RequestMoodMeterValueAnimation();

	virtual void NativeConstruct() override;

	
};
