#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ContentWidget.h"
#include "MoodLevelSelectWidget.generated.h"

class UMoodCyberButton;

UCLASS()

class UMoodLevelSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* LevelSelectButtonLevel1;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UMoodCyberButton* LevelSelectButtonLevel2;

	UPROPERTY(meta = (BindWidget))
	UMoodCyberButton* CloseLevelSelectButton;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenWidget();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CloseWidget();

	void ShowWidget();
	void HideWidget();

	UFUNCTION()
	void LoadLevelOne();
	UFUNCTION()
	void LoadLevelTwo();


};
