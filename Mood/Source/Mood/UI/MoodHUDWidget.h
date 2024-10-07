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
struct FInputModeUIOnly;

UCLASS()

class UMoodHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget))
	UMoodPlayerHealthBar* HealthBar;

	UPROPERTY()
	UMoodHealthComponent* HealthComponent;
	UPROPERTY()
	UMoodWeaponComponent* WeaponComponent;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodLostScreen* LostScreen;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodWinScreen* WinScreen;

	UPROPERTY(meta =(BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodMoodMeterWidget* MoodMeterWidget;

	UPROPERTY(meta =(BindWidget), BlueprintReadWrite, EditAnywhere)
	UMoodAmmoWidget* AmmoWidget;

	//Spin radial variables
	UPROPERTY()
	float InnerCircleSpin = 0.3f;
	UPROPERTY()
	float MiddleCircleSpin = 0.2f;
	UPROPERTY()
	float OuterCircleSpin = 0.1f;
	//text change variable
	UPROPERTY()
	float MoodMeterNumber = 0.f;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void GetHealthComponent();

	UFUNCTION(Blueprintable)
	void DisplayLostScreen();

	virtual void NativeConstruct() override;

	
};
