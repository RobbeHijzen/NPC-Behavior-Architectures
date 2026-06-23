#include "UAS_Spectating.h"
#include "../../../Pedestrians/NPCSpatialGrid.h"
#include "../../../Pedestrians/ConversationSubsystem.h"

void UUAS_Spectating::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		pedestrian->SetAnimation(EAnimationType::Walking, true);
		moveComp->SetMovementState(MovementState::Wander);

		moveComp->LeaveLaneForLocation(pedestrian->GetActorLocation() + 0.5f * (pedestrian->GetConfrontTransform().GetLocation() - pedestrian->GetActorLocation()));
	}
}

void UUAS_Spectating::TickState(float deltaTime, APedestrian* pedestrian)
{
	pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_Spectating::UtilityFunction(APedestrian* pedestrian)
{
	bool hasNearbyConversation{ false };

	TArray<AActor*> actors{};
	GetWorld()->GetSubsystem<UNPCSpatialGrid>()->QueryRadius(pedestrian->GetActorLocation(), 1000.f, actors);
	auto conversationSubsystem = GetWorld()->GetSubsystem<UConversationSubsystem>();

	for (auto actor : actors)
	{
		if (conversationSubsystem->HasActiveToken(actor))
		{
			FTransform transform{};
			transform.SetLocation(pedestrian->GetActorLocation() + 0.9 * (actor->GetActorLocation() - pedestrian->GetActorLocation()));
			transform.SetRotation((FRotator{ actor->GetActorRotation() - pedestrian->GetActorRotation() }).Quaternion());

			pedestrian->SetConfrontTransform(transform);

			hasNearbyConversation = true;
		}
	}
	return FMath::FRand() * 0.5f * (int)hasNearbyConversation;
}