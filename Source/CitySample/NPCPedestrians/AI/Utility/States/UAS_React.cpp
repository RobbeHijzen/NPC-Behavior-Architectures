#include "UAS_React.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

void UUAS_React::BeginPlay(APedestrian* pedestrian, UWorld* world)
{
	_PedestrianReference = pedestrian;
}

void UUAS_React::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (_PedestrianReference)
	{
		_PedestrianReference->SetAnimation(EAnimationType::Reacting, true);
	}

	if (auto moveComp = _PedestrianReference->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetMovementState(MovementState::Idle);
	}
}

void UUAS_React::TickState(float deltaTime, APedestrian* pedestrian)
{
	_PedestrianReference->AddToData("Threat", deltaTime * _ThreatChange);
	_PedestrianReference->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_PedestrianReference->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_React::UtilityFunction(APedestrian* pedestrian)
{
	float threat{ _PedestrianReference->GetData("Threat") };

	return -FMath::Square((threat -0.4f) * 3) + 1.f;
}
