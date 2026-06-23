#include "UAS_Wander.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

void UUAS_Wander::BeginPlay(APedestrian* pedestrian, UWorld* world)
{
	_PedestrianReference = pedestrian;
}

void UUAS_Wander::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (_PedestrianReference)
	{
		_PedestrianReference->SetAnimation(EAnimationType::Walking, true);
	}

	if (auto moveComp = _PedestrianReference->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetMovementState(MovementState::Wander);
	}
}

void UUAS_Wander::TickState(float deltaTime, APedestrian* pedestrian)
{
	_PedestrianReference->AddToData("Threat", deltaTime * _ThreatChange);
	_PedestrianReference->AddToData("Fatigue", deltaTime * _FatigueChange);
	_PedestrianReference->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_PedestrianReference->AddToData("Suspicion", deltaTime * _SuspicionChange);


}

float UUAS_Wander::UtilityFunction(APedestrian* pedestrian)
{
	float fatigue{ _PedestrianReference->GetData("Fatigue") };

	return 0.5f - fatigue / 2.f;
}
