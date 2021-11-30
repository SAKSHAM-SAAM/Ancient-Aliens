// SAKSHAM SHARMA 2021


#include "ShooterCharacter.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "ShooterGameModeBase.h"
#include "Blueprint/UserWidget.h"

// Sets default values 
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//SetRootComponent(Root);
	
	//Character = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character"));
	//Character->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	weapon->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Keyboard Bind
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveBackward"), this, &AShooterCharacter::MoveBackward);
	PlayerInputComponent->BindAxis(TEXT("MoveLeft"), this, &AShooterCharacter::MoveLeft);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	// Mouse Bind
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	// Keyboard Action Bind
	PlayerInputComponent->BindAction(TEXT("Jump") ,EInputEvent::IE_Pressed ,this , &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Trigger") ,EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("SuperJump"),EInputEvent::IE_Pressed, this, &AShooterCharacter::SuperJump);
}
void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}
void AShooterCharacter::MoveBackward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}
void AShooterCharacter::MoveLeft(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}
void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}
void AShooterCharacter::Shoot()
{
	weapon->PullTrigger();
}
void AShooterCharacter::SuperJump()
{
	UE_LOG(LogTemp,Warning,TEXT("Super Jump"));
	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//SetRootComponent(Root);
	Character = GetMesh();
	
	if(JumpCounter < 1)
	{
		UGameplayStatics::SpawnEmitterAttached(Booster, Character, TEXT("FX_Piston_l"));
		UGameplayStatics::SpawnEmitterAttached(Booster, Character, TEXT("FX_Piston_r"));
		UGameplayStatics::SpawnSoundAttached(SuperJumpSFX, Character, TEXT("FX_Piston_r"));

		ACharacter::LaunchCharacter(FVector(0, 0, JumpHeight), false, true);
		JumpCounter++;
	}
}
void AShooterCharacter::Landed(const FHitResult &Hit)
{
	JumpCounter=0;
}
float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) 
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	if(Health == 0){
		Dead=true;
	} 
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if(isDead())
	{
		AShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AShooterGameModeBase>();
		if(GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}
bool AShooterCharacter::isDead() const
{
	return Dead;
}
float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}