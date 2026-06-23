#include "BTT_LeaveLaneForSmartObject.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_LeaveLaneForSmartObject::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* controller = OwnerComp.GetAIOwner();
    if (!controller) return EBTNodeResult::Failed;

    APawn* pawn = controller->GetPawn();
    if (!pawn) return EBTNodeResult::Failed;

    APedestrian* pedestrian = Cast<APedestrian>(pawn);
    if (!pedestrian) return EBTNodeResult::Failed;


	if ((_MoveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>()))
	{
		if (_MoveComp->LeaveLaneForSmartObject(_SmartObjectTag))
		{
			_MoveComp->SetOffLaneAnimationType(_AnimationTypeWhenAtLocation);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}