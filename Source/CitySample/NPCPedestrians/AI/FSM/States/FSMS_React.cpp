#include "FSMS_React.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../Transitions/FSMT_Timer.h"
#include "../FSMComponent.h"
#include "FSMS_Wander.h"

void UFSMS_React::BeginPlay(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);

	AddTransition(new FSMT_Timer(_OwnerComponent->GetStateOfClass<UFSMS_Wander>(), world, Cast<APedestrian>(pawn)->GetAnimationLength(EAnimationType::Reacting)));
}

void UFSMS_React::EnterState(APawn* pawn, UWorld* world)
{
	if (_Pedestrian)
	{
		_Pedestrian->SetAnimation(EAnimationType::Reacting, false);
	}

	if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetMovementState(MovementState::Idle);
	}
}

void UFSMS_React::TickState(float deltaTime, APawn* pawn)
{
	_Pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	_Pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_Pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}
