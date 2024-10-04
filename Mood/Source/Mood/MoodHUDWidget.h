#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodHUDWidget.generated.h"


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

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void GetHealthComponent();

	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	
};
