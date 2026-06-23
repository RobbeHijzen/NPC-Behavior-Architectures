#include "HFSMS_Idle.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../Transitions/HFSMT_CheckData.h"
#include "../HFSMComponent.h"
#include "HFSMS_Wander.h"
#include "HFSMS_Flee.h"
#include "HFSMS_React.h"

void UHFSMS_Idle::BeginPlay(APawn* pawn, UWorld* world)
{
	AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Wander>(), world, Cast<APedestrian>(pawn), "Fatigue", EFloatComparison::LessOrEqual, 0.f));
}

void UHFSMS_Idle::EnterState(APawn* pawn, UWorld* world)
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

void UHFSMS_Idle::TickState(float deltaTime, APawn* pawn)
{
	_Pedestrian->AddToData("Fatigue", deltaTime * _FatigueChange);
}
