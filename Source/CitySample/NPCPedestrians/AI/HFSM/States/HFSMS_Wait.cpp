#include "HFSMS_Wait.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../HFSMComponent.h"
#include "HFSMS_Wander.h"
#include "../Transitions/HFSMT_IsAtRedLight.h"

void UHFSMS_Wait::BeginPlay(APawn* pawn, UWorld* world)
{
	AddTransition(new HFSMT_IsAtRedLight(_OwnerComponent->GetStateOfClass<UHFSMS_Wander>(), world, Cast<APedestrian>(pawn), true));
}

void UHFSMS_Wait::EnterState(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);
	if (_Pedestrian)
	{
		_Pedestrian->SetAnimation(EAnimationType::Idle, true);
	}

	if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetMovementState(MovementState::Idle);
	}
}