#include "STT_ModifyData.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FSTT_ModifyData::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FModifyDataTaskInstanceData& data = Context.GetInstanceData(*this);

	data.Pedestrian = Cast<APedestrian>(data.Actor);

	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FSTT_ModifyData::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FModifyDataTaskInstanceData& data = Context.GetInstanceData(*this);

	if (data.Pedestrian)
	{
		data.OutputValue = data.Pedestrian->AddToData(data.DataName, data.ValuePerSecond * DeltaTime);
	}

	return EStateTreeRunStatus::Running;
}
