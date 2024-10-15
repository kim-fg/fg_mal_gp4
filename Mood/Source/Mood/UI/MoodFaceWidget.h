#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodFaceWidget.generated.h"

class UImage;

UCLASS()
class UMoodFaceWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* HPFace1;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* HPFace2;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* HPFace3;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* HPFace4;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* HPFace5;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* Face666One;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* Face666Two;

	UPROPERTY(EditAnywhere)
	bool IsMoodMeterUI;

	UPROPERTY(Blueprintable, BlueprintReadWrite)
	bool HurtAnimationIsPlaying;

	UFUNCTION(BlueprintNativeEvent)
	void PlayHurtAnimation();
	
	UFUNCTION(BlueprintNativeEvent)
	void PlayLaughingAnimation();

protected:
	virtual void NativeConstruct() override;
};
