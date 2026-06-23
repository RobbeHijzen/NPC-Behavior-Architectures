#include "BTT_Evade.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_Evade::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* controller = OwnerComp.GetAIOwner();
    if (!controller) return EBTNodeResult::Failed;

    APawn* pawn = controller->GetPawn();
    if (!pawn) return EBTNodeResult::Failed;

    APedestrian* pedestrian = Cast<APedestrian>(pawn);
    if (!pedestrian) return EBTNodeResult::Failed;


	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetLocationToEvade(pedestrian->GetSuspicionLocation());
		moveComp->SetEvadeLocation(true);

		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UBTT_Evade::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) return;

	APawn* pawn = controller->GetPawn();
	if (!pawn) return;

	if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetEvadeLocation(false);
	}
}
