#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodHitmarkerWidget.generated.h"

class UImage;

UCLASS()
class UMoodHitmarkerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void PlayHitmarkerAnimation();

protected:
	UPROPERTY(meta =(BindWidget), BlueprintReadWrite)
	UImage* HitmarkerTopLeft;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* HitmarkerTopRight;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* HitmarkerBottomRight;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* HitmarkerBottomLeft;

	UPROPERTY(BlueprintReadWrite)
	bool HitmarkerAnimationPlaying;

	virtual void NativeConstruct() override;

;		
};