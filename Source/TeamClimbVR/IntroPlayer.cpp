#include "IntroPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "TimerManager.h"

AIntroPlayer::AIntroPlayer()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AIntroPlayer::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PC) return;

    PC->PlayerCameraManager->StartCameraFade(
        0.0f, 1.0f, 0.01f,
        FLinearColor::Black,
        false,
        true
    );

    FTimerHandle FadeInHandle;
    GetWorld()->GetTimerManager().SetTimer(
        FadeInHandle,
        this,
        &AIntroPlayer::FadeInFromBlack,
        2.0f,
        false
    );
}

void AIntroPlayer::FadeInFromBlack()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PC) return;

    PC->PlayerCameraManager->StartCameraFade(
        1.0f, 0.0f, 2.0f,
        FLinearColor::Black,
        false,
        false
    );
}