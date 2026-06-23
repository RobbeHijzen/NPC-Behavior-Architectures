#include "UAS_Flee.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

void UUAS_Flee::BeginPlay(APedestrian* pedestrian, UWorld* world)
{
	_PedestrianReference = pedestrian;
}

void UUAS_Flee::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (_PedestrianReference)
	{
		_PedestrianReference->SetAnimation(EAnimationType::Running, true);
	}

	if (auto moveComp = _PedestrianReference->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetMovementState(MovementState::Run);
	}
}

void UUAS_Flee::TickState(float deltaTime, APedestrian* pedestrian)
{
	_PedestrianReference->AddToData("Threat", deltaTime * _ThreatChange);
	_PedestrianReference->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_PedestrianReference->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_Flee::UtilityFunction(APedestrian* pedestrian)
{
	float threat{ _PedestrianReference->GetData("Threat") };

	return FMath::Sqrt(FMath::Sqrt(threat));
}