// SAKSHAM SHARMA 2021


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
    if(LoseScreen == nullptr)
    {
        return;
    }
    LoseScreen->AddToViewport();
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
