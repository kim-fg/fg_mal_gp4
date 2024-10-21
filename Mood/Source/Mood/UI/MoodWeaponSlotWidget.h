#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoodWeaponSlotWidget.generated.h"

class UTextBlock;
class UMoodWeaponSlotComponent;
class UMoodWeaponComponent;

UCLASS()
class UMoodWeaponSlotWidget : public UUserWidget
{

	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	void GetWeaponSlotComponent(UMoodWeaponSlotComponent* NewWeaponSlotComponent);

	void GetWeaponArray();

protected:

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Slot1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Slot2;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Slot3;

	UPROPERTY()
	UMoodWeaponSlotComponent* WeaponSlotComponent;

	UPROPERTY()
	TArray<UMoodWeaponComponent*> WeaponsArray;

	UPROPERTY()
	UMoodWeaponComponent* EquippedWeapon;

	UPROPERTY()
	TArray<UTextBlock*> WeaponSlotWidgetArray;
};