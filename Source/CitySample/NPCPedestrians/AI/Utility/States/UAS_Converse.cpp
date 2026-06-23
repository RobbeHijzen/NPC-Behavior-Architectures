#include "UAS_Converse.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../../../Pedestrians/ConversationSubsystem.h"

void UUAS_Converse::BeginPlay(APedestrian* pedestrian, UWorld* world)
{
	_PedestrianReference = pedestrian;

}

void UUAS_Converse::EnterState(APedestrian* pedestrian, UWorld* world)
{
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
				_IsConversing = true;
				moveComp->SetMovementState(MovementState::Wander);
				moveComp->LeaveLaneForLocation(token->MeetingLocation);

				GetWorld()->GetTimerManager().SetTimer(_ConversationTimerHandle, [moveComp, this]()
					{
						if (IsValid(moveComp))
						{
							moveComp->ReturnToLane();
						}
						_IsConversing = false;

					}, token->Duration, false);
			}
		}
	}
}

void UUAS_Converse::ExitState(APedestrian* pedestrian)
{
	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->ReturnToLane();
	}
}

void UUAS_Converse::TickState(float deltaTime, APedestrian* pedestrian)
{
	_PedestrianReference->AddToData("Threat", deltaTime * _ThreatChange);
	_PedestrianReference->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_PedestrianReference->AddToData("Suspicion", deltaTime * _SuspicionChange);
}

float UUAS_Converse::UtilityFunction(APedestrian* pedestrian)
{
	bool hasPendingInvite{ false };

	auto conversationSubsystem = GetWorld()->GetSubsystem<UConversationSubsystem>();
	if (conversationSubsystem)
	{
		auto token = conversationSubsystem->GetPendingInvite(pedestrian);
		if (token)
		{
			hasPendingInvite = true;
		}
	}

	return _PedestrianReference->GetData("SocialNeed") * (1 + int(_IsConversing)) + hasPendingInvite;
}
