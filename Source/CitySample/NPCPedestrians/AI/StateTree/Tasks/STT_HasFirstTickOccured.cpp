#include "STT_HasFirstTickOccured.h"
#include "StateTreeExecutionContext.h"


EStateTreeRunStatus FSTT_HasFirstTickOccured::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FSTT_HasFirstTickOccured::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FHasFirstTickOccuredTaskInstanceData& data = Context.GetInstanceData(*this);

	data.HasFirstTickOccured = true;

	return EStateTreeRunStatus::Succeeded;
}
