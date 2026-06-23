#include "UAS_Reporting.h"


void UUAS_Reporting::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (pedestrian)
	{
		pedestrian->SetAnimation(EAnimationType::PhoneCall, true);
		if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
		{
			moveComp->SetMovementState(MovementState::Idle);
		}
	}
}

void UUAS_Reporting::TickState(float deltaTime, APedestrian* pedestrian)
{
	pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_Reporting::UtilityFunction(APedestrian* pedestrian)
{
	float suspicion{ pedestrian->GetData("Suspicion") };

	return suspicion;
}