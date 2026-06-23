#include "BTT_PlayAnimation.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_PlayAnimation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* controller = OwnerComp.GetAIOwner();
    if (!controller) return EBTNodeResult::Failed;

    APawn* pawn = controller->GetPawn();
    if (!pawn) return EBTNodeResult::Failed;

    APedestrian* pedestrian = Cast<APedestrian>(pawn);
    if (!pedestrian) return EBTNodeResult::Failed;


    pedestrian->SetAnimation(_AnimationType, _LoopAnimation);

    if (!_LoopAnimation)
    {
        GetWorld()->GetTimerManager().SetTimer(_TimerHandle, [this]()
            {
                _HasFinishedAnimation = true;
            }, pedestrian->GetAnimationLength(_AnimationType), false);

        return EBTNodeResult::InProgress;
    }

    if(_DoSucceed)
        return EBTNodeResult::Succeeded;

    return EBTNodeResult::InProgress;
}

void UBTT_PlayAnimation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    if (_HasFinishedAnimation)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}

void UBTT_PlayAnimation::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    GetWorld()->GetTimerManager().ClearTimer(_TimerHandle);
    _HasFinishedAnimation = false;
}
