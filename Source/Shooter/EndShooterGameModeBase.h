// SAKSHAM SHARMA 2021

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameModeBase.h"
#include "EndShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AEndShooterGameModeBase : public AShooterGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PawnKilled(APawn* PawnKilled) override;
private:
	void EndGame(bool bIsPlayerWinner);
};
