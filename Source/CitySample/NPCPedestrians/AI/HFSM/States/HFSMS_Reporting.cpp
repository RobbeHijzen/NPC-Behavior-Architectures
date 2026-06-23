#include "HFSMS_Reporting.h"

#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../HFSMComponent.h"
#include "HFSMS_Wander.h"
#include "GameplayTagsManager.h"
#include "../Transitions/HFSMT_Timer.h"
#include "../Transitions/HFSMT_CheckData.h"

void UHFSMS_Reporting::BeginPlay(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);

	AddTransition(new HFSMT_Timer(_OwnerComponent->GetStateOfClass<UHFSMS_Wander>(), world, _Pedestrian->GetAnimationLength(EAnimationType::PhoneCall)));
}

void UHFSMS_Reporting::EnterState(APawn* pawn, UWorld* world)
{
	if (_Pedestrian)
	{
		_Pedestrian->SetAnimation(EAnimationType::PhoneCall, true);
		if (auto moveComp = _Pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
		{
			moveComp->SetMovementState(MovementState::Idle);
		}
	}
}