#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodPlayerHealthbar.generated.h"

class UProgressBar;


UCLASS()
class UMoodPlayerHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetHealthbarPercentage(float NewPercentage);

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Healthbar;



protected:

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float FilledPercentage;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditAnywhere)
	float FillRateMultiplier;
};
