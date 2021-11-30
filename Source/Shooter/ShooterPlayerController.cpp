// SAKSHAM SHARMA 2021


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    HUD = CreateWidget(this, Crosshair);
    if(HUD == nullptr)
    {
        return;
    }
    HUD->AddToViewport();
}

void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    
    HUD->RemoveFromViewport();
    // GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
    if(bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen == nullptr)
        {
            return;
        }
        WinScreen->AddToViewport();
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen == nullptr)
        {
            return;
        }
        LoseScreen->AddToViewport();
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

