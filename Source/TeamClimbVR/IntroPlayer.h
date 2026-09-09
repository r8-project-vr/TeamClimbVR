#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
    void FadeInFromBlack();
};