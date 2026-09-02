// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

void UMyGameInstance::ResetGameData()
{
    ClearTime = 0.0f;
    EnemyHitCount = 0;

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("GAME DATA RESET")
    );
}