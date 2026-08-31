#include "ATeleportTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/BoxComponent.h"

AATeleportTrigger::AATeleportTrigger()
{
    PrimaryActorTick.bCanEverTick = true;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    RootComponent = Box;

    Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Box->SetCollisionObjectType(ECC_WorldStatic);
    Box->SetCollisionResponseToAllChannels(ECR_Overlap);

    Box->OnComponentBeginOverlap.AddDynamic(this, &AATeleportTrigger::OnOverlapBegin);
}

void AATeleportTrigger::BeginPlay()
{
    Super::BeginPlay();
}

void AATeleportTrigger::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bUseHandDistanceTrigger)
    {
        CheckHandDistance();
    }
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
    TriggerTeleport();
}

void AATeleportTrigger::CheckHandDistance()
{
    APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!Pawn) return;

    USceneComponent* Left = nullptr;
    USceneComponent* Right = nullptr;

    TArray<USceneComponent*> Comps;
    Pawn->GetComponents(Comps);

    for (USceneComponent* Comp : Comps)
    {
        const FString Name = Comp->GetName();
        if (Name.Contains("HandLeft"))
            Left = Comp;
        else if (Name.Contains("HandRight"))
            Right = Comp;
    }

    if (!Left || !Right) return;

    float Dist = FVector::Distance(
        Left->GetComponentLocation(),
        Right->GetComponentLocation()
    );

    // ① まだ距離チェックを開始していない → 手が近いか確認
    if (!bReadyToCheckDistance)
    {
        if (Dist < HandDistanceThreshold)
        {
            bReadyToCheckDistance = true;   // 手が近づいたのでチェック開始
        }
        return; // まだ離れ判定はしない
    }

    // ② 距離チェック開始後 → 離れたら発火
    if (Dist > HandDistanceThreshold)
    {
        TriggerTeleport();
    }
}


void AATeleportTrigger::TriggerTeleport()
{
    if (bTriggered) return;
    bTriggered = true;

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PC) return;

    PC->PlayerCameraManager->StartCameraFade(
        0.0f,
        1.0f,
        1.0f,
        FLinearColor::Black,
        false,
        true
    );

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

