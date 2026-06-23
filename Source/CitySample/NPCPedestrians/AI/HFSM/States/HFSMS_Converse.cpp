#include "HFSMS_Converse.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../../../Pedestrians/ConversationSubsystem.h"
#include "../Transitions/HFSMT_Timer.h"
#include "../HFSMComponent.h"
#include "HFSMS_Wander.h"
#include "../Transitions/HFSMT_CheckData.h"

void UHFSMS_Converse::BeginPlay(APawn* pawn, UWorld* world)
{
}

void UHFSMS_Converse::EnterState(APawn* pawn, UWorld* world)
{
	if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
	{
		auto conversationSubsystem = GetWorld()->GetSubsystem<UConversationSubsystem>();
		if (conversationSubsystem)
		{
			auto token = conversationSubsystem->GetPendingInvite(pawn);
			if (token)
			{
				conversationSubsystem->AcceptConversation(pawn, token);
			}
			else
			{
				token = conversationSubsystem->TryStartConversation(pawn, 500.f);
			}

			if (token)
			{
				moveComp->SetMovementState(MovementState::Wander);
				moveComp->LeaveLaneForLocation(token->MeetingLocation);

				GetWorld()->GetTimerManager().SetTimer(_ConversationTimerHandle, [moveComp]()
					{
						if (IsValid(moveComp))
						{
							moveComp->ReturnToLane();
						}

					}, token->Duration, false);

				AddTransition(new HFSMT_Timer(_OwnerComponent->GetStateOfClass<UHFSMS_Wander>(), world, token->Duration));
			}
		}
	}
}