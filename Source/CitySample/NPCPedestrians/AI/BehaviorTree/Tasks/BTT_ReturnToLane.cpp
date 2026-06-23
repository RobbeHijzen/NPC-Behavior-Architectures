#include "BTT_ReturnToLane.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_ReturnToLane::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* controller = OwnerComp.GetAIOwner();
    if (!controller) return EBTNodeResult::Failed;

    APawn* pawn = controller->GetPawn();
    if (!pawn) return EBTNodeResult::Failed;

    APedestrian* pedestrian = Cast<APedestrian>(pawn);
    if (!pedestrian) return EBTNodeResult::Failed;

	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->ReturnToLane();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
