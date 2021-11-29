// SAKSHAM SHARMA 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AWeapon;

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// BLUEPRINT PURE FUNCTION TO SEE IF PLAYER IS Alive
	UFUNCTION(BlueprintPure)
	bool isDead() const;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// overriding damge function
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();
private:
	void MoveForward(float AxisValue);
	void MoveBackward(float AxisValue);
	void MoveLeft(float AxisValue);
	void MoveRight(float AxisValue);

	
	void SuperJump();
	/*
	void LookUp(float AxisValue);
	void LookDown(float AxisValue);
	void LookRight(float AxisValue);
	void LookLeft(float AxisValue);
	*/
	UPROPERTY(EditDefaultsOnly)
	bool Dead = false;

	UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
	AWeapon* weapon;

//------------------------------------------------------------------------
	// SAKSHAM SHARMA'S TEST AREA
	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Character;

	UPROPERTY(EditAnywhere)
	UParticleSystem* Booster;

	UPROPERTY(EditAnywhere)
	float JumpHeight;

	UPROPERTY(EditAnywhere)
	int JumpCounter;

	virtual void Landed(const FHitResult& Hit) override;
};
