#include "FSMS_Converse.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../../../Pedestrians/ConversationSubsystem.h"
#include "../Transitions/FSMT_Timer.h"
#include "../FSMComponent.h"
#include "FSMS_Wander.h"
#include "../Transitions/FSMT_CheckData.h"
#include "FSMS_Flee.h"
#include "FSMS_React.h"

void UFSMS_Converse::BeginPlay(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);

	AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Flee>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.5f));
	AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_React>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.3f));
}

void UFSMS_Converse::EnterState(APawn* pawn, UWorld* world)
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

				AddTransition(new FSMT_Timer(_OwnerComponent->GetStateOfClass<UFSMS_Wander>(), world, token->Duration));
			}
		}
	}
}

void UFSMS_Converse::TickState(float deltaTime, APawn* pawn)
{
	_Pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	_Pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_Pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}