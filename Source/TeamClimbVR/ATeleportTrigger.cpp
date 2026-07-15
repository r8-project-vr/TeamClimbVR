// Fill out your copyright notice in the Description page of Project Settings.


#include "ATeleportTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"

// Sets default values
AATeleportTrigger::AATeleportTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionObjectType(ECC_WorldStatic);
	Box->SetCollisionResponseToAllChannels(ECR_Overlap);

	Box->OnComponentBeginOverlap.AddDynamic(this, &AATeleportTrigger::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AATeleportTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void AATeleportTrigger::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!OtherActor) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return;

	// 暗転（フェードアウト）
	PC->PlayerCameraManager->StartCameraFade(
		0.0f,        // From
		1.0f,        // To
		1.0f,        // Duration
		FLinearColor::Black,
		false,       // bShouldFadeAudio
		true         // bHoldWhenFinished
	);

	// 1秒後にレベル切り替え
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		[this]()
		{
			UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
		},
		1.0f,
		false
	);
}