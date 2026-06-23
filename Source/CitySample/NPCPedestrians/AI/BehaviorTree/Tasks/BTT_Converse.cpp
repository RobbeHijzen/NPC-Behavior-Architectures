#include "BTT_Converse.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "AIController.h"
#include "../../../Pedestrians/ConversationSubsystem.h"

EBTNodeResult::Type UBTT_Converse::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) return EBTNodeResult::Failed;

	APawn* pawn = controller->GetPawn();
	if (!pawn) return EBTNodeResult::Failed;

	APedestrian* pedestrian = Cast<APedestrian>(pawn);
	if (!pedestrian) return EBTNodeResult::Failed;


	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		auto conversationSubsystem = GetWorld()->GetSubsystem<UConversationSubsystem>();
		if (conversationSubsystem)
		{
			auto token = conversationSubsystem->GetPendingInvite(pedestrian);
			if (token)
			{
				conversationSubsystem->AcceptConversation(pedestrian, token);
			}
			else
			{
				token = conversationSubsystem->TryStartConversation(pedestrian, 500.f);
			}

			if (token)
			{
				moveComp->SetMovementState(MovementState::Wander);
				moveComp->SetOffLaneAnimationType(EAnimationType::Idle);
				moveComp->LeaveLaneForLocation(token->MeetingLocation);

				GetWorld()->GetTimerManager().SetTimer(_ConversingTimerHandle, [moveComp, this]()
					{
						if (IsValid(moveComp))
						{
							moveComp->ReturnToLane();
						}
						_DoneWithConversing = true;

					}, token->Duration, false);

				return EBTNodeResult::InProgress;
			}
		}
	}
	return EBTNodeResult::Failed;
}

void UBTT_Converse::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (_DoneWithConversing)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTT_Converse::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
		_DoneWithConversing = false;
		GetWorld()->GetTimerManager().ClearTimer(_ConversingTimerHandle);
}
