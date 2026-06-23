#include "HFSMS_Evading.h"

#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../HFSMComponent.h"
#include "HFSMS_Wander.h"
#include "GameplayTagsManager.h"
#include "../Transitions/HFSMT_Timer.h"
#include "../Transitions/HFSMT_CheckData.h"

void UHFSMS_Evading::BeginPlay(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);

	AddTransition(new HFSMT_Timer(_OwnerComponent->GetStateOfClass<UHFSMS_Wander>(), world, FMath::RandRange(40.f, 60.f)));
}

void UHFSMS_Evading::EnterState(APawn* pawn, UWorld* world)
{
	if (_Pedestrian)
	{
		_Pedestrian->SetAnimation(EAnimationType::Walking, true);
		if (auto moveComp = _Pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
		{
			moveComp->SetLocationToEvade(_Pedestrian->GetSuspicionLocation());
			moveComp->SetEvadeLocation(true);

			moveComp->SetMovementState(MovementState::Wander);
		}
	}
}