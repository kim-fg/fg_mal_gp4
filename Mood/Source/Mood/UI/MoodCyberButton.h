#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodCyberButton.generated.h"

class UTextBlock;
class UButton;
struct FSlateBrush;
struct FButtonStyle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonHovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonUnhovered);

UCLASS()
class UMoodCyberButton : public UUserWidget
{

	GENERATED_BODY()
public:
	UPROPERTY(meta =(BindWidget), BlueprintReadWrite)
	UButton* Button;

	UPROPERTY(meta =(BindWidgetOptional), BlueprintReadWrite)
	UTextBlock* ButtonText;

	UPROPERTY(EditAnywhere)
	FText ButtonFText;

	UPROPERTY(EditAnywhere)
	FColor ButtonColor;

	UPROPERTY(EditAnywhere)
	FColor TextColor;

	FButtonClicked ButtonClickedSig;
	UFUNCTION(Blueprintable)
	void OnButtonClicked();
	
	FButtonHovered ButtonHoveredSig;
	UFUNCTION(Blueprintable)
	void OnButtonHovered();
	
	FButtonUnhovered ButtonUnhoveredSig;
	UFUNCTION(Blueprintable)
	void OnButtonUnhovered();
	
	
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;
};
