// Fill out your copyright notice in the Description page of Project Settings.

#include "GameResultManager.h"
#include "MyGameInstance.h"

AGameResultManager::AGameResultManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AGameResultManager::BeginPlay()
{
    Super::BeginPlay();

    StartTime = GetWorld()->GetTimeSeconds();

    UE_LOG(LogTemp, Warning, TEXT("START TIME: %f"), StartTime);
}

void AGameResultManager::EnemyWasHit()
{
    UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>();

    if (GameInstance)
    {
        GameInstance->EnemyHitCount++;

        UE_LOG(
            LogTemp,
            Warning,
            TEXT("ENEMY HIT COUNT: %d"),
            GameInstance->EnemyHitCount
        );
    }
}

void AGameResultManager::GameCleared()
{
    UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>();

    if (GameInstance)
    {
        GameInstance->ClearTime =
            GetWorld()->GetTimeSeconds() - StartTime;

        UE_LOG(
            LogTemp,
            Warning,
            TEXT("CLEAR TIME: %f"),
            GameInstance->ClearTime
        );
    }
}