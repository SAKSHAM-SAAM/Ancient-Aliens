// SAKSHAM SHARMA 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void GameHasEnded(class AActor *EndGameFocus = nullptr, bool bIsWinner = false) override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> Crosshair;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5;

	FTimerHandle RestartTimer;

	UUserWidget* HUD;
};
