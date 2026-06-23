#include "BTS_ModifyData.h"
#include "AIController.h"
#include "../../../Pedestrians/Pedestrian.h"

UBTS_ModifyData::UBTS_ModifyData()
{
    bNotifyTick = true;
    Interval = 0.f;
    RandomDeviation = 0.f;
}

void UBTS_ModifyData::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* controller = OwnerComp.GetAIOwner();
    if (!controller) return;

    APedestrian* pedestrian = Cast<APedestrian>(controller->GetPawn());
    if (!pedestrian) return;

    pedestrian->AddToData(DataName, ValuePerSecond * DeltaSeconds);
}
