#include "BTT_SetMovementState.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_SetMovementState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* controller = OwnerComp.GetAIOwner();
    if (!controller) return EBTNodeResult::Failed;

    APawn* pedestrian = controller->GetPawn();
    if (!pedestrian) return EBTNodeResult::Failed;

    if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
    {
        moveComp->SetMovementState(_NewMovementState);
        return EBTNodeResult::Succeeded;
    }

	return EBTNodeResult::Failed;
}
