// SAKSHAM SHARMA 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class SHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	void PullTrigger();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere);
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere);
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000; 

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitFlash;

	UPROPERTY(EditAnywhere)
	float WeaponDamage;
};
