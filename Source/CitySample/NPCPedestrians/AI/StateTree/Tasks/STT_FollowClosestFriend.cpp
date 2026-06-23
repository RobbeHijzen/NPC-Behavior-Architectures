#include "STT_FollowClosestFriend.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FSTT_FollowClosestFriend::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FFollowFriendTaskInstanceData& data = Context.GetInstanceData(*this);

	if (auto moveComp = data.Actor->GetComponentByClass<UPedestrianMovementComponent>())
	{
		auto pedestrian{ Cast<APedestrian>(data.Actor) };
		pedestrian->SetAnimation(EAnimationType::Walking, true);

		moveComp->SetMovementState(MovementState::Wander);

		data.ClosestFriend = pedestrian->GetClosestFriend();
		data.MoveComp = moveComp;
		moveComp->LeaveLaneForLocation(data.ClosestFriend->GetActorLocation());

		return EStateTreeRunStatus::Running;
	}
	return EStateTreeRunStatus::Failed;
}

EStateTreeRunStatus FSTT_FollowClosestFriend::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FFollowFriendTaskInstanceData& data = Context.GetInstanceData(*this);

	data.MoveComp->LeaveLaneForLocation(data.ClosestFriend->GetActorLocation());

	return EStateTreeRunStatus::Running;
}
