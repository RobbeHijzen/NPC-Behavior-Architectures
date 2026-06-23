#include "HFSMS_Flee.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../Transitions/HFSMT_CheckData.h"
#include "../HFSMComponent.h"
#include "HFSMS_Wander.h"

void UHFSMS_Flee::BeginPlay(APawn* pawn, UWorld* world)
{
	AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Wander>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::LessOrEqual, 0.2f));
}

void UHFSMS_Flee::EnterState(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);
	if (_Pedestrian)
	{
		_Pedestrian->SetAnimation(EAnimationType::Running, true);
	}

	if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetMovementState(MovementState::Run);
	}
}