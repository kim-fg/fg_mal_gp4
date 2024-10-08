#include "MoodWeaponSlotComponent.h"
#include "MoodWeaponComponent.h"
#include "MoodWeaponPickup.h"
#include "GameFramework/Character.h"

UMoodWeaponSlotComponent::UMoodWeaponSlotComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	UMoodWeaponSlotComponent::SetAutoActivate(true);
}

bool UMoodWeaponSlotComponent::AddWeapon(UMoodWeaponComponent* Weapon) {
	if (!Owner || !Weapon) {
		return false;
	}

	if (Weapons.Contains(Weapon)) {
		return false;
	}

	Weapons.Add(Weapon);
	
	FAttachmentTransformRules AttachmentRules(
		EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld, true
	);
	auto OwnerMesh = Owner->GetMesh();
	if (!OwnerMesh) {
		UE_LOG(LogTemp, Log, TEXT("Failed to get Owner Mesh"));
	}
	
	auto AttachSuccess = Weapon->AttachToComponent(Owner->GetMesh(), AttachmentRules, FName(TEXT("GripPoint")));

	if (!AttachSuccess) {
		UE_LOG(LogTemp, Log, TEXT("%s failed to attach weapon (%s)"),
			*Owner->GetActorNameOrLabel(), *Weapon->GetAnimationID()
		);
	}

	// add the weapon as an instance component to the character
	Owner->AddInstanceComponent(Weapon);
	
	if (AutoSelectNewWeapon) {
		SelectWeapon(Weapons.Num() - 1);
	}

	return true;
}

void UMoodWeaponSlotComponent::EnableSelectedWeapon() {
	for (int i = 0; i < Weapons.Num(); i++) {
		auto WeaponActive = i == SelectedWeaponIndex;
		auto Weapon = Weapons[i];
		Weapon->SetVisibility(WeaponActive);
		Weapon->SetActive(WeaponActive);
	}

	UE_LOG(LogTemp, Log, TEXT("Selected %ls"), *Weapons[SelectedWeaponIndex]->GetAnimationID());
}

void UMoodWeaponSlotComponent::SelectNextWeapon() {
	SelectWeapon(SelectedWeaponIndex + 1);
}

void UMoodWeaponSlotComponent::SelectPreviousWeapon() {
	SelectWeapon(SelectedWeaponIndex - 1);
}

void UMoodWeaponSlotComponent::SelectWeapon(const int Index) {
	// selected weapon out of range
	if (Index < 0 || Index >= Weapons.Num()) {
		return;
	}

	// dont select the same weapon twice
	if (SelectedWeaponIndex == Index) {
		return;
	}

	SelectedWeaponIndex = Index;
	EnableSelectedWeapon();
}

UMoodWeaponComponent* UMoodWeaponSlotComponent::GetSelectedWeapon() {
	if (Weapons.Num() < 1) { return nullptr; }
	return Weapons[SelectedWeaponIndex];
}


void UMoodWeaponSlotComponent::UseSelectedWeapon() {
	// We dont have any weapons
	if (Weapons.Num() == 0) {
		return;
	}
	
	// Selected weapon is out of bounds
	if (SelectedWeaponIndex < 0 || SelectedWeaponIndex >= Weapons.Num()) {
		return;
	}

	auto SelectedWeapon = Weapons[SelectedWeaponIndex];
	auto MuzzleOrigin = MuzzleRoot ? MuzzleRoot->GetComponentLocation() : Owner->GetActorLocation();
	auto MuzzleDirection = MuzzleRoot ? MuzzleRoot->GetForwardVector() : Owner->GetActorForwardVector();
	auto WeaponUsedSuccess = SelectedWeapon->Use(MuzzleOrigin + MuzzleOffset, MuzzleDirection);

	if (WeaponUsedSuccess) {
		OnWeaponUsed.Broadcast(SelectedWeapon);
	}
}

void UMoodWeaponSlotComponent::AddAmmo(TSubclassOf<AMoodWeaponPickup> WeaponClass, int Amount) {
	auto TargetWeapon = Weapons.FindByPredicate([&](const UMoodWeaponComponent* Weapon) {
		return Weapon->GetClass() == WeaponClass;
	});
	
	if (!TargetWeapon) { return; }
	
	(*TargetWeapon)->AddAmmo(Amount);
}

void UMoodWeaponSlotComponent::BeginPlay() {
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	for (auto i = 0; i < DefaultWeapons.Num(); i++) {
		auto WeaponPickup = GetWorld()->SpawnActor<AMoodWeaponPickup>(DefaultWeapons[i]);
		AddWeapon(WeaponPickup->GetWeapon());
	}
}

void UMoodWeaponSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!HasWeapon()) { return;	}	
	if (!TriggerHeld) { return;	}
	
	UseSelectedWeapon();
}


