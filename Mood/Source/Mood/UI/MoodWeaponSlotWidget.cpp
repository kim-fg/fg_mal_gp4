#include "MoodWeaponSlotWidget.h"
#include "../Weapons/MoodWeaponSlotComponent.h"
#include "../Weapons/MoodWeaponComponent.h"
#include "Components/TextBlock.h"

void UMoodWeaponSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Slot1->SetText(FText::FromString(""));
	Slot2->SetText(FText::FromString(""));
	Slot3->SetText(FText::FromString(""));
	WeaponSlotWidgetArray.Add(Slot1);
	WeaponSlotWidgetArray.Add(Slot2);
	WeaponSlotWidgetArray.Add(Slot3);
}

void UMoodWeaponSlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	WeaponsArray = WeaponSlotComponent->GetWeaponArray();
	EquippedWeapon = WeaponSlotComponent->GetSelectedWeapon();

	for (int i = 0; i < WeaponsArray.Num(); i++)
	{
		if (i <= 2)
		{
			WeaponSlotWidgetArray[i]->SetText(FText::FromString(FString::FromInt(i + 1)));
			if (EquippedWeapon == WeaponsArray[i])
			{
				if (WeaponSlotWidgetArray[i] != nullptr)
					WeaponSlotWidgetArray[i]->SetText(FText::FromString("[ " + FString::FromInt(i + 1) + " ]"));
			}
		}
	}

}

void UMoodWeaponSlotWidget::GetWeaponSlotComponent(UMoodWeaponSlotComponent* NewWeaponSlotComponent)
{
	this->WeaponSlotComponent = NewWeaponSlotComponent;
	GetWeaponArray();
}

void UMoodWeaponSlotWidget::GetWeaponArray()
{
	WeaponsArray = WeaponSlotComponent->GetWeaponArray();
}
