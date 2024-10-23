#include "MoodEnemyCharacter.h"

#include "Components/SphereComponent.h"
#include "Mood/MoodGameMode.h"
#include "Mood/MoodHealthComponent.h"
#include "Mood/Player/MoodCharacter.h"
#include "Mood/Weapons/MoodWeaponSlotComponent.h"

AMoodEnemyCharacter::AMoodEnemyCharacter() {
	ActivationSphere = CreateDefaultSubobject<USphereComponent>("Activation Sphere");
	ActivationSphere->SetupAttachment(RootComponent);
	

	Health = CreateDefaultSubobject<UMoodHealthComponent>(TEXT("Health"));

	WeaponSlot = CreateDefaultSubobject<UMoodWeaponSlotComponent>(TEXT("Weapon Slot"));
}

void AMoodEnemyCharacter::BeginPlay() {
	Super::BeginPlay();
	ActivationSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMoodEnemyCharacter::OnActivationOverlap);
	Health->OnHurt.AddUniqueDynamic(this, &AMoodEnemyCharacter::LoseHealth);

	MoodGameMode = Cast<AMoodGameMode>(GetWorld()->GetAuthGameMode());
}

void AMoodEnemyCharacter::LoseHealth(int Amount, int NewHealth) {
	MoodGameMode->ChangeMoodValue(Amount);
	MoodGameMode->ResetDamageTime();

	if (!CanSeePlayer())
	{
		UE_LOG(LogTemp, Log, TEXT("Enemy's visibility increased"));
		ActivationSphere->SetSphereRadius(FLT_MAX, true);
	}
}

void AMoodEnemyCharacter::SetPlayer(AMoodCharacter* InPlayer) {
	// don't allow un-setting player
	if (!InPlayer) { return; }
	
	Player = InPlayer;
	// I assume beginplay runs BEFORE this. we'll see :shrug: -KIM
	ActivationSphere->OnComponentBeginOverlap.RemoveAll(this);
	OnPlayerSeen.Broadcast(Player);
}

void AMoodEnemyCharacter::ScanForPlayer() {
	if (CanSeePlayer()) {
		GetWorldTimerManager().ClearTimer(PlayerScanTimer);
		ActivationSphere->OnComponentBeginOverlap.RemoveAll(this);
		OnPlayerSeen.Broadcast(Player);
	}
}

bool AMoodEnemyCharacter::CanSeePlayer() {
	if (!Player) { return false; }

	auto PlayerCenter = Player->GetActorLocation();
	auto SelfEyes = GetActorLocation() + FVector::UnitZ() * 90.0f;

	FCollisionQueryParams CollisionQueryParams{};
	CollisionQueryParams.AddIgnoredActor(this);
	
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
	if (Player) { return; }
	
	auto OtherAsPlayer = Cast<AMoodCharacter>(OtherActor);
	if (!OtherAsPlayer) { return; }

	Player = OtherAsPlayer;

	GetWorldTimerManager().SetTimer(
		PlayerScanTimer, this, &AMoodEnemyCharacter::ScanForPlayer,
		0.1f, true, 0.0f
	);
}