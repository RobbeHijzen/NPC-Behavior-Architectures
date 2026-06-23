#include "UAS_Investigating.h"

void UUAS_Investigating::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		pedestrian->SetAnimation(EAnimationType::Walking, true);

		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForLocation(pedestrian->GetSuspicionLocation());
	}
}

void UUAS_Investigating::TickState(float deltaTime, APedestrian* pedestrian)
{
	pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_Investigating::UtilityFunction(APedestrian* pedestrian)
{
	float suspicion{ pedestrian->GetData("Suspicion") };

	return -FMath::Square((suspicion - 0.7f) * 3) + 1.f;
}