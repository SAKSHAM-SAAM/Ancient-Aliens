// SAKSHAM SHARMA 2021


#include "EndShooterGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"

void AEndShooterGameModeBase::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    //UE_LOG(LogTemp, Warning, TEXT("A pawn was killed"));
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

}
void AEndShooterGameModeBase::EndGame(bool bIsPlayerWinner)
{
    for(AController* Controller : TActorRange<AController>(GetWorld()) )
    {
        bool bIsWinner=Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}