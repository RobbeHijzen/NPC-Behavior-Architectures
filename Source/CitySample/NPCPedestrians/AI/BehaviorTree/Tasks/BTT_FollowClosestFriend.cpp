#include "BTT_FollowClosestFriend.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_FollowClosestFriend::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

		_ClosestFriend = pedestrian->GetClosestFriend();
		_MoveComp = moveComp;
		moveComp->LeaveLaneForLocation(_ClosestFriend->GetActorLocation());

		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UBTT_FollowClosestFriend::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	_MoveComp->LeaveLaneForLocation(_ClosestFriend->GetActorLocation());
}
