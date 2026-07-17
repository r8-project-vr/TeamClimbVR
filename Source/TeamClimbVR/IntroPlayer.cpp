#include "IntroPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

AIntroPlayer::AIntroPlayer()
{
    PrimaryActorTick.bCanEverTick = true;

    LogoWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LogoWidget"));
    LogoWidget->SetupAttachment(RootComponent);

    LogoWidget->SetWidgetSpace(EWidgetSpace::World);
    LogoWidget->SetDrawSize(FVector2D(1024, 512));
    LogoWidget->SetPivot(FVector2D(0.5f, 0.5f));
    LogoWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    LogoWidget->SetTickWhenOffscreen(true);
    LogoWidget->SetTwoSided(true);
    LogoWidget->SetBlendMode(EWidgetBlendMode::Transparent);
    LogoWidget->SetBackgroundColor(FLinearColor::Transparent);

    LogoWidget->SetTranslucentSortPriority(9999);
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

    FVector CamLoc;
    FRotator CamRot;
    PC->GetPlayerViewPoint(CamLoc, CamRot);

    LogoWidget->SetWidgetClass(LogoWidgetClass);
    LogoWidget->SetWorldLocation(CamLoc + CamRot.Vector() * 150.0f);
    LogoWidget->SetWorldRotation(CamRot);

    ShowTitleLogo();

    FTimerHandle FadeInHandle;
    GetWorld()->GetTimerManager().SetTimer(
        FadeInHandle,
        this,
        &AIntroPlayer::FadeInFromBlack,
        2.0f,
        false
    );
}

void AIntroPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bLogoFading)
    {
        LogoFadeCurrent += DeltaTime;
        float Alpha = FMath::Clamp(LogoFadeCurrent / LogoFadeTime, 0.0f, 1.0f);

        float Opacity = 1.0f - Alpha;

        if (UUserWidget* W = LogoWidget->GetUserWidgetObject())
        {
            W->SetRenderOpacity(Opacity);
        }

        if (Alpha >= 1.0f)
        {
            bLogoFading = false;
            LogoWidget->SetVisibility(false);
        }
    }


    FVector CamLoc;
    FRotator CamRot;
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerViewPoint(CamLoc, CamRot);

    LogoWidget->SetWorldLocation(CamLoc + CamRot.Vector() * 150.0f);
    LogoWidget->SetWorldRotation(CamRot);
}

void AIntroPlayer::ShowTitleLogo()
{
    // Widget ‚Í BeginPlay ‚ÅƒZƒbƒgÏ‚Ý‚È‚Ì‚Å‰½‚à‚µ‚È‚¢
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

    FTimerHandle LogoFadeHandle;
    GetWorld()->GetTimerManager().SetTimer(
        LogoFadeHandle,
        this,
        &AIntroPlayer::StartLogoFadeOut,
        1.0f,
        false
    );
}

void AIntroPlayer::StartLogoFadeOut()
{
    bLogoFading = true;
    LogoFadeCurrent = 0.0f;
}
