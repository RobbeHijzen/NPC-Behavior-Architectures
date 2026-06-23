#include "BTT_Confront.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_Confront::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

		moveComp->LeaveLaneForLocation(pedestrian->GetActorLocation() + _DistancePercentage * (pedestrian->GetConfrontTransform().GetLocation() - pedestrian->GetActorLocation()));

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
