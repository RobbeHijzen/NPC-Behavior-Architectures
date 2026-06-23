#include "NPCPedestrians/AI/StateTree/Tasks/STT_MoveToSuspicion.h"
#include "StateTreeExecutionContext.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

EStateTreeRunStatus FSTT_MoveToSuspicion::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FMoveToSuspicionTaskInstanceData& data = Context.GetInstanceData(*this);

	if (auto moveComp = data.Actor->GetComponentByClass<UPedestrianMovementComponent>())
	{
		auto pedestrian{ Cast<APedestrian>(data.Actor) };
		pedestrian->SetAnimation(EAnimationType::Walking, true);

		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForLocation(pedestrian->GetSuspicionLocation());

		return EStateTreeRunStatus::Running;
	}

	return EStateTreeRunStatus::Failed;
}
