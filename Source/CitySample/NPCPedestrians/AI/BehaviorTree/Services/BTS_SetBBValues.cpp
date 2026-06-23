#include "BTS_SetBBValues.h"
#include "AIController.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_SetBBValues::UBTS_SetBBValues()
{
    bNotifyTick = true;
    Interval = 0.f;
    RandomDeviation = 0.f;
}

void UBTS_SetBBValues::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* controller = OwnerComp.GetAIOwner();
    if (!controller) return;

    APedestrian* pedestrian = Cast<APedestrian>(controller->GetPawn());
    if (!pedestrian) return;

    UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
    if (!blackboard) return;

    float fatigue{ pedestrian->GetData("Fatigue") };
    blackboard->SetValueAsFloat(FName{ "Fatigue" }, fatigue);

    float threat{ pedestrian->GetData("Threat") };
    blackboard->SetValueAsFloat(FName{ "Threat" }, threat);

    float socialNeed{ pedestrian->GetData("SocialNeed") };
    blackboard->SetValueAsFloat(FName{ "SocialNeed" }, socialNeed);

    float suspicion{ pedestrian->GetData("Suspicion") };
    blackboard->SetValueAsFloat(FName{ "Suspicion" }, suspicion);
}
