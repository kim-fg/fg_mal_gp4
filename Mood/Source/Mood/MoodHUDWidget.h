#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodHUDWidget.generated.h"


class UMoodWinScreen;
class UMoodLostScreen;
class UMoodPlayerHealthBar;
class UMoodHealthComponent;

UCLASS()

class UMoodHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget))
	UMoodPlayerHealthBar* HealthBar;

	UPROPERTY()
	UMoodHealthComponent* HealthComponent;

	UPROPERTY(meta = (BindWidget))
	UMoodLostScreen* LostScreen;

	UPROPERTY(meta = (BindWidget))
	UMoodWinScreen* WinScreen;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void GetHealthComponent();

	UFUNCTION(Blueprintable)
	void DisplayLostScreen();

	virtual void NativeConstruct() override;

	
};
