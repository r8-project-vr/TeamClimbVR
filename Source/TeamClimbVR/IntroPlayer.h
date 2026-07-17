#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "IntroPlayer.generated.h"

UCLASS()
class TEAMCLIMBVR_API AIntroPlayer : public AActor
{
    GENERATED_BODY()

public:
    AIntroPlayer();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "Intro")
    TSubclassOf<UUserWidget> LogoWidgetClass;

    UPROPERTY()
    UWidgetComponent* LogoWidget;

    float LogoFadeTime = 1.5f;
    float LogoFadeCurrent = 0.0f;
    bool bLogoFading = false;

    void ShowTitleLogo();
    void FadeInFromBlack();
    void StartLogoFadeOut();
};
