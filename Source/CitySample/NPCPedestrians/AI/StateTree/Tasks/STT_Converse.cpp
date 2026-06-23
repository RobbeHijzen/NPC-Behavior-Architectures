#include "STT_Converse.h"
#include "StateTreeExecutionContext.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../../../Pedestrians/ConversationSubsystem.h"

EStateTreeRunStatus FSTT_Converse::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FConverseTaskInstanceData& data = Context.GetInstanceData(*this);
	APawn* actor{ data.Actor };

	if (auto moveComp = actor->GetComponentByClass<UPedestrianMovementComponent>())
	{
		auto conversationSubsystem = Context.GetWorld()->GetSubsystem<UConversationSubsystem>();
		if (conversationSubsystem)
		{
			auto token = conversationSubsystem->GetPendingInvite(actor);
			if (token)
			{
				conversationSubsystem->AcceptConversation(actor, token);
			}
			else
			{
				token = conversationSubsystem->TryStartConversation(actor, 500.f);
			}

			if (token)
			{
				moveComp->SetMovementState(MovementState::Wander);
				moveComp->SetOffLaneAnimationType(EAnimationType::Idle);
				moveComp->LeaveLaneForLocation(token->MeetingLocation);

				Context.GetWorld()->GetTimerManager().SetTimer(data.ConversingTimerHandle, [moveComp, &data]()
					{
						if (IsValid(moveComp))
						{
							moveComp->ReturnToLane();
						}
						data.DoneWithConversing = true;

					}, token->Duration, false);

				return EStateTreeRunStatus::Running;
			}
		}
	}
	return EStateTreeRunStatus::Failed;
}

EStateTreeRunStatus FSTT_Converse::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FConverseTaskInstanceData& data = Context.GetInstanceData(*this);
	if (data.DoneWithConversing)
	{
		return EStateTreeRunStatus::Succeeded;
	}
	return EStateTreeRunStatus::Running;
}


void FSTT_Converse::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	if (auto world = Context.GetWorld())
	{
		FConverseTaskInstanceData& data = Context.GetInstanceData(*this);
		data.DoneWithConversing = false;
		world->GetTimerManager().ClearTimer(data.ConversingTimerHandle);
	}
}