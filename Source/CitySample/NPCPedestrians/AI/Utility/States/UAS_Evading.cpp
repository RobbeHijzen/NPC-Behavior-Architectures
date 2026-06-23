#include "UAS_Evading.h"

void UUAS_Evading::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (pedestrian)
	{
		pedestrian->SetAnimation(EAnimationType::Walking, true);
		if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
		{
			moveComp->SetLocationToEvade(pedestrian->GetSuspicionLocation());
			moveComp->SetEvadeLocation(true);

			moveComp->SetMovementState(MovementState::Wander);
		}
	}
}

void UUAS_Evading::TickState(float deltaTime, APedestrian* pedestrian)
{
	pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_Evading::UtilityFunction(APedestrian* pedestrian)
{
	float suspicion{ pedestrian->GetData("Suspicion") };

	return -FMath::Square((suspicion - 0.4f) * 3) + 1.f;
}