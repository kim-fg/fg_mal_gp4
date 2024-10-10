#include "MoodEnemyCharacter.h"

#include "Components/SphereComponent.h"
#include "Mood/MoodGameMode.h"
#include "Mood/MoodHealthComponent.h"
#include "Mood/Player/MoodCharacter.h"
#include "Mood/Weapons/MoodWeaponSlotComponent.h"

AMoodEnemyCharacter::AMoodEnemyCharacter() {
	ActivationSphere = CreateDefaultSubobject<USphereComponent>("Activation Sphere");
	ActivationSphere->SetupAttachment(RootComponent);
	ActivationSphere->OnComponentBeginOverlap.AddDynamic(this, &AMoodEnemyCharacter::OnActivationOverlap);

	Health = CreateDefaultSubobject<UMoodHealthComponent>(TEXT("Health"));
	Health->OnHurt.AddUniqueDynamic(this, &AMoodEnemyCharacter::LoseHealth);

	WeaponSlot = CreateDefaultSubobject<UMoodWeaponSlotComponent>(TEXT("Weapon Slot"));
}

void AMoodEnemyCharacter::BeginPlay() {
	Super::BeginPlay();

	MoodGameMode = Cast<AMoodGameMode>(GetWorld()->GetAuthGameMode());
}

void AMoodEnemyCharacter::LoseHealth(int Amount, int NewHealth) {
	MoodGameMode->ChangeMoodValue(Amount);
}

bool AMoodEnemyCharacter::CanSeePlayer() {
	if (!Player) { return false; }

	auto PlayerCenter = Player->GetActorLocation();
	auto SelfEyes = GetActorLocation() + FVector::UnitZ() * 90.0f;

	FCollisionQueryParams CollisionQueryParams{};
	CollisionQueryParams.AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), SelfEyes, PlayerCenter, FColor::Yellow, false, 3.0f);
	
	FHitResult OutHit{};
	GetWorld()->LineTraceSingleByChannel(
		OutHit, SelfEyes, PlayerCenter,
		ECC_Visibility, CollisionQueryParams
	);

	if (!OutHit.IsValidBlockingHit()) { return false; }

	auto HitActor = OutHit.GetActor();
	if (!HitActor) { return false; }
	return HitActor == Player;
}

void AMoodEnemyCharacter::OnActivationOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                              const FHitResult& SweepResult) {
	auto OtherAsPlayer = Cast<AMoodCharacter>(OtherActor);
	if (!OtherAsPlayer) { return; }

	Player = OtherAsPlayer;
	if (CanSeePlayer()) {
		ActivationSphere->OnComponentBeginOverlap.RemoveAll(this);
		OnPlayerSeen.Broadcast(Player);
		return;
	}

	// TODO! Start looking for player line of sight every frame
}
