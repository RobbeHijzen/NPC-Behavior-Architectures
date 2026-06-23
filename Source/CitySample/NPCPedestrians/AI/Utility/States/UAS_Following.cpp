#include "UAS_Following.h"
#include "../../../Pedestrians/NPCSpatialGrid.h"

void UUAS_Following::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (pedestrian)
	{
		pedestrian->SetAnimation(EAnimationType::Walking, true);
		if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
		{
			moveComp->SetMovementState(MovementState::Wander);
			moveComp->LeaveLaneForLocation(pedestrian->GetClosestFriend()->GetActorLocation());
		}
	}
}

void UUAS_Following::TickState(float deltaTime, APedestrian* pedestrian)
{
	pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_Following::UtilityFunction(APedestrian* pedestrian)
{
	bool hasFriendNearby{ false };
	int friendGroup{ pedestrian->GetFriendGroup() };

	TArray<AActor*> actors{};
	GetWorld()->GetSubsystem<UNPCSpatialGrid>()->QueryRadius(pedestrian->GetActorLocation(), 1000.f, actors);

	for (auto actor : actors)
	{
		if (friendGroup == pedestrian->GetFriendGroup())
		{
			pedestrian->SetClosestFriend(pedestrian);
			hasFriendNearby = true;
		}
	}

	return FMath::FRand() * 0.5f * hasFriendNearby;
}