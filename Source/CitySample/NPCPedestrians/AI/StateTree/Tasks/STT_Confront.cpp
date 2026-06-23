#include "STT_Confront.h"
#include "StateTreeExecutionContext.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

EStateTreeRunStatus FSTT_Confront::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FConfrontTaskInstanceData& data = Context.GetInstanceData(*this);

	if (auto moveComp = data.Actor->GetComponentByClass<UPedestrianMovementComponent>())
	{
		auto pedestrian{ Cast<APedestrian>(data.Actor) };
		pedestrian->SetAnimation(EAnimationType::Walking, true);
		moveComp->SetMovementState(MovementState::Wander);

		moveComp->LeaveLaneForLocation(pedestrian->GetActorLocation() + data.DistancePercentage * (pedestrian->GetConfrontTransform().GetLocation() - pedestrian->GetActorLocation()));

		return EStateTreeRunStatus::Running;
	}
	return EStateTreeRunStatus::Failed;
}
