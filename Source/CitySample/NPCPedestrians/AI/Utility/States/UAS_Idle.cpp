#include "UAS_Idle.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

void UUAS_Idle::BeginPlay(APedestrian* pedestrian, UWorld* world)
{
	_PedestrianReference = pedestrian;
}

void UUAS_Idle::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (_PedestrianReference)
	{
		_PedestrianReference->SetAnimation(EAnimationType::Idle, true);
	}

	if (auto moveComp = _PedestrianReference->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetMovementState(MovementState::Idle);
	}
}

void UUAS_Idle::TickState(float deltaTime, APedestrian* pedestrian)
{
	_PedestrianReference->AddToData("Threat", deltaTime * _ThreatChange);
	_PedestrianReference->AddToData("Fatigue", deltaTime * _FatigueChange);
	_PedestrianReference->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_PedestrianReference->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

void UUAS_Idle::ExitState(APedestrian* pedestrian)
{
	_PedestrianReference->AddToData("Fatigue", -1.f);
}

float UUAS_Idle::UtilityFunction(APedestrian* pedestrian)
{
	float fatigue{ _PedestrianReference->GetData("Fatigue") };

	return fatigue / 2.f;
}
