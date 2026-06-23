#include "STT_PlayAnimation.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FSTT_PlayAnimation::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FPlayAnimationTaskInstanceData& data = Context.GetInstanceData(*this);

	if (auto actor = data.Actor)
	{
		if (auto pedestrian = Cast<APedestrian>(actor))
		{
			pedestrian->SetAnimation(data.AnimationType, data.LoopAnimation);

			if (data.LoopAnimation)
			{
				return EStateTreeRunStatus::Running;
			}
			else
			{
				Context.GetWorld()->GetTimerManager().SetTimer(data.AnimationTimerHandle, [&data]()
					{
						data.HasFinishedAnimation = true;
					},
					pedestrian->GetAnimationLength(data.AnimationType), false);

				return EStateTreeRunStatus::Running;
			}
		}
	}

	return EStateTreeRunStatus::Failed;
}

EStateTreeRunStatus FSTT_PlayAnimation::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FPlayAnimationTaskInstanceData& data = Context.GetInstanceData(*this);

	if (!data.LoopAnimation)
	{
		if (data.HasFinishedAnimation)
		{
			return EStateTreeRunStatus::Succeeded;
		}
	}

	return EStateTreeRunStatus::Running;
}
