// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATeleportTrigger.generated.h"

class UBoxComponent;

UCLASS()
class TEAMCLIMBVR_API AATeleportTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATeleportTrigger();

protected:
	// Called when the game starts or when spawned
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Teleport")
	FName NextLevelName = "NextLevel";

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Box;

};
