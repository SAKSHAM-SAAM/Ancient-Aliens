// SAKSHAM SHARMA 2021


#include "EndShooterGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AEndShooterGameModeBase::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    //UE_LOG(LogTemp, Warning, TEXT("A pawn was killed"));
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    // Loop over all AIController Character
    for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()) )
    {
        if (!Controller->isDead())
        {
            return;
        }
    }
    
    EndGame(true);

}
void AEndShooterGameModeBase::EndGame(bool bIsPlayerWinner)
{
    for(AController* Controller : TActorRange<AController>(GetWorld()) )
    {
        bool bIsWinner=Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}