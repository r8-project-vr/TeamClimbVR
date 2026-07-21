// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UCLASS()
class TEAMCLIMBVR_API AGoal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Scene Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* RootSceneComponent;
	//Box Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionComponent;
	//Set Level name to changeScene
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetupLevel")
	FName LevelName;
	//Collision
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	//Effect
	UFUNCTION(BlueprintImplementableEvent, Category = "Effects")
	void OnPlayerReachedGoal();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
