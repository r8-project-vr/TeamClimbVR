// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameResultManager.generated.h"

UCLASS()
class TEAMCLIMBVR_API AGameResultManager : public AActor
{
    GENERATED_BODY()

public:

    AGameResultManager();

protected:

    virtual void BeginPlay() override;

public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Results")
    float StartTime = 0.0f;

    UFUNCTION(BlueprintCallable)
    void EnemyWasHit();

    UFUNCTION(BlueprintCallable)
    void GameCleared();
};