#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodMoodStage.generated.h"

class UImage;
class UMoodFaceWidget;
UCLASS()
class UMoodMoodStage : public UUserWidget
{
	GENERATED_BODY()

public:

	/*
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite);
	UMoodFaceWidget* LaughingSkull;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite);
	UImage* StageNumber;
*/
	UFUNCTION(BlueprintNativeEvent)
	void PlayStageAnimation();
protected:

	virtual void NativeConstruct() override;
	
private:


};