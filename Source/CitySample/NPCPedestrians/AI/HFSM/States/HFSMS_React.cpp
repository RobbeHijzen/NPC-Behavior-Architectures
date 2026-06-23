#include "HFSMS_React.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../Transitions/HFSMT_Timer.h"
#include "../HFSMComponent.h"
#include "HFSMS_Wander.h"

void UHFSMS_React::BeginPlay(APawn* pawn, UWorld* world)
{
	AddTransition(new HFSMT_Timer(_OwnerComponent->GetStateOfClass<UHFSMS_Wander>(), world, Cast<APedestrian>(pawn)->GetAnimationLength(EAnimationType::Reacting)));
}

void UHFSMS_React::EnterState(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);
	if (_Pedestrian)
	{
		_Pedestrian->SetAnimation(EAnimationType::Reacting, false);
	}

	if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetMovementState(MovementState::Idle);
	}
}