// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoal::AGoal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootSceneComponent;
	//Setup Collision Component
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComponent->SetupAttachment(RootSceneComponent);
	//setup size
	CollisionComponent->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	//setup with OnOverlapBegin
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	//Check hit
	if (OtherActor && OtherActor != this && OtherActor->IsA(APawn::StaticClass()))
	{
		//close the collision check
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//Effect
		OnPlayerReachedGoal();
		/*if stage name set do scene change
		if (!ResultLevelName.IsNone())
		{
			UGameplayStatics::OpenLevel(this, ResultLevelName);
		}*/
	}
}