#include "STT_LeaveLaneForSmartObject.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FSTT_LeaveLaneForSmartObject::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FLeaveLaneTaskInstanceData& data = Context.GetInstanceData(*this);

	if ((data.MoveComp = data.Actor->GetComponentByClass<UPedestrianMovementComponent>()))
	{
		if (data.MoveComp->LeaveLaneForSmartObject(data.SmartObjectTag))
		{
			data.RandomDuration = FMath::RandRange(data.MinDuration, data.MaxDuration);
			data.MoveComp->SetOffLaneAnimationType(data.AnimationTypeWhenAtLocation);

			return EStateTreeRunStatus::Running;
		}
	}

	return EStateTreeRunStatus::Failed;
}

EStateTreeRunStatus FSTT_LeaveLaneForSmartObject::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FLeaveLaneTaskInstanceData& data = Context.GetInstanceData(*this);

	if (data.MoveComp && data.MoveComp->GetFollowerState() == EFollowerState::OffLane)
	{
		data.CurrentDuration += DeltaTime;
		if (data.CurrentDuration >= data.RandomDuration)
		{
			return EStateTreeRunStatus::Succeeded;
		}
	}

	return EStateTreeRunStatus::Running;
}

void FSTT_LeaveLaneForSmartObject::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FLeaveLaneTaskInstanceData& data = Context.GetInstanceData(*this);
	data.CurrentDuration = 0.f;

	if (data.MoveComp)
	{
		data.MoveComp->ReturnToLane();
	}
}
