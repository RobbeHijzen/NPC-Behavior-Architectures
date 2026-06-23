#include "STT_Evade.h"
#include "StateTreeExecutionContext.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

EStateTreeRunStatus FSTT_Evade::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FEvadeTaskInstanceData& data = Context.GetInstanceData(*this);

	if (auto moveComp = data.Actor->GetComponentByClass<UPedestrianMovementComponent>())
	{
		auto pedestrian{ Cast<APedestrian>(data.Actor) };

		moveComp->SetLocationToEvade(pedestrian->GetSuspicionLocation());
		moveComp->SetEvadeLocation(true);

		return EStateTreeRunStatus::Running;
	}
	return EStateTreeRunStatus::Failed;
}

void FSTT_Evade::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FEvadeTaskInstanceData& data = Context.GetInstanceData(*this);

	if (auto moveComp = data.Actor->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetEvadeLocation(false);
	}
}
