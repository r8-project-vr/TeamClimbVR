// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
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

    bool bReadyToCheckDistance = false;   // Žè‚ª‹ß‚Ã‚­‚Ü‚Å‘Ò‚Â
    bool bTriggered = false;


    virtual void Tick(float DeltaTime) override;

    void CheckHandDistance();
    void TriggerTeleport();
};
