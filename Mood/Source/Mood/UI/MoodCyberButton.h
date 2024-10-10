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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Blueprintable, BlueprintCallable, BlueprintAssignable)
	FButtonClicked ButtonClickedSig;
	UFUNCTION(Blueprintable)
	void OnButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Blueprintable, BlueprintCallable, BlueprintAssignable)
	FButtonHovered ButtonHoveredSig;
	UFUNCTION(Blueprintable)
	void OnButtonHovered();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Blueprintable, BlueprintCallable, BlueprintAssignable)
	FButtonUnhovered ButtonUnhoveredSig;
	UFUNCTION(Blueprintable)
	void OnButtonUnhovered();
	
	
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;
};
