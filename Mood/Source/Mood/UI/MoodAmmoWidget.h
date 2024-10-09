#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodAmmoWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class UMoodAmmoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta =(BindWidget))
	UTextBlock* AmmoText;

	UPROPERTY(meta =(BindWidget))
	UTextBlock* AmmoTextInfinite;

	UPROPERTY(meta =(BindWidget))
	UImage* AmmoIcon;
};
