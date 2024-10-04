#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MoodHUD.generated.h"

class UMoodPlayerHealthBar;
class UMoodHUDWidget;
class UMoodHealthComponent;

UCLASS()
class AMoodHUD : public AHUD
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
	UMoodHUDWidget* MainWidget;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	AMoodHUD();

	void GetPlayerHealthComponent();

};
