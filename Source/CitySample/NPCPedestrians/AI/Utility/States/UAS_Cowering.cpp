#include "UAS_Cowering.h"


void UUAS_Cowering::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (pedestrian)
	{
		pedestrian->SetAnimation(EAnimationType::Cower, true);
		if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
		{
			moveComp->SetMovementState(MovementState::Idle);
		}
	}
}

void UUAS_Cowering::TickState(float deltaTime, APedestrian* pedestrian)
{
	pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_Cowering::UtilityFunction(APedestrian* pedestrian)
{
	float threat{ pedestrian->GetData("Threat") };

	return threat * threat;
}