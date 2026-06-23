#include "BTS_RandomChancePerSecond.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_RandomChancePerSecond::UBTS_RandomChancePerSecond()
{
    bNotifyTick = true;
    Interval = 0.f;
    RandomDeviation = 0.f;
}

void UBTS_RandomChancePerSecond::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (!BB) return;

    const float roll = FMath::FRand();
    bool succeeded{ roll < _ChancePerSecond * DeltaSeconds };

    BB->SetValueAsBool(FName{"RandomChanceSucceeded"}, succeeded);

    if (succeeded)
    {
        GetWorld()->GetTimerManager().SetTimerForNextTick([BB]()
            {
                BB->SetValueAsBool(FName{ "RandomChanceSucceeded" }, false);
            });
    }
}
