#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "ATeleportTrigger.generated.h"

UCLASS()
class TEAMCLIMBVR_API AATeleportTrigger : public AActor
{
    GENERATED_BODY()

public:
    AATeleportTrigger();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
    FName NextLevelName = "NextLevel";

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* Box;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
    float HandDistanceThreshold = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
    bool bUseHandDistanceTrigger = false;

    // Åö å¯â âπçƒê∂óp
    UPROPERTY(VisibleAnywhere)
    UAudioComponent* AudioComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
    USoundBase* SoundEffect;

    bool bReadyToCheckDistance = false;
    bool bTriggered = false;

    virtual void Tick(float DeltaTime) override;

    void CheckHandDistance();
    void TriggerTeleport();

    void PlaySE();
};
