#include "BTT_MoveToSuspicion.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_MoveToSuspicion::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* controller = OwnerComp.GetAIOwner();
    if (!controller) return EBTNodeResult::Failed;

    APawn* pawn = controller->GetPawn();
    if (!pawn) return EBTNodeResult::Failed;

    APedestrian* pedestrian = Cast<APedestrian>(pawn);
    if (!pedestrian) return EBTNodeResult::Failed;

	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		pedestrian->SetAnimation(EAnimationType::Walking, true);

		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForLocation(pedestrian->GetSuspicionLocation());

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
