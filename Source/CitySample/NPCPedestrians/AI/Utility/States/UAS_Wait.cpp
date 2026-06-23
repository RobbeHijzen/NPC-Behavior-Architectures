#include "UAS_Wait.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

void UUAS_Wait::BeginPlay(APedestrian* pedestrian, UWorld* world)
{
	_PedestrianReference = pedestrian;
	_PedestrianMoveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>();

}

void UUAS_Wait::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (pedestrian)
	{
		pedestrian->SetAnimation(EAnimationType::Idle, true);
	}

	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetMovementState(MovementState::Idle);
	}
}

void UUAS_Wait::TickState(float deltaTime, APedestrian* pedestrian)
{
	_PedestrianReference->AddToData("Threat", deltaTime * _ThreatChange);
	_PedestrianReference->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_PedestrianReference->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_Wait::UtilityFunction(APedestrian* pedestrian)
{
	return !_PedestrianMoveComp->IsCurrentLaneWalkable();
}
