#include "STT_SetMovementState.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FSTT_SetMovementState::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FSetMovementStateTaskInstanceData& data = Context.GetInstanceData(*this);

	if (auto actor = data.Actor)
	{
		if (auto movementComp = actor->GetComponentByClass<UPedestrianMovementComponent>())
		{
			movementComp->SetMovementState(data.NewMovementState);
			return EStateTreeRunStatus::Running;
		}
	}

	return EStateTreeRunStatus::Failed;
}
