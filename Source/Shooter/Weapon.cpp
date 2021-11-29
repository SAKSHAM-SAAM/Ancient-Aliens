// SAKSHAM SHARMA 2021


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::PullTrigger()
{
	// Spawn Emitter at location of muzzle
	// UE_LOG(LogTemp, Warning, TEXT("Trigger Pulled"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
	if(OwnerController == nullptr) return;

	// - - - - - - - - - - 
	FVector Location ;
	FRotator Rotation ;
	// Out parameters used here
	OwnerController->GetPlayerViewPoint(Location,Rotation);

	// Adding Trace Ray to spawn at a location with roation vector of camera
	// Location of veiwport + rotation of viewport in vector format  + maximum range to map
	FVector End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit,Location,End,ECollisionChannel::ECC_GameTraceChannel1, Params);

	if(bSuccess)
	{
		FVector ShotDirection= -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, Hit.Location,ShotDirection.Rotation());

		AActor* ActorHit = Hit.GetActor();
		if(ActorHit != nullptr)
		{
			FPointDamageEvent DamageEvent(WeaponDamage, Hit, ShotDirection, nullptr);
			ActorHit->TakeDamage(WeaponDamage, DamageEvent, OwnerController, this);
		}
	}
	// Used to capture viewport
	// DrawDebugCamera(GetWorld() ,Location ,Rotation ,90 ,2 ,FColor::Red ,true);
}