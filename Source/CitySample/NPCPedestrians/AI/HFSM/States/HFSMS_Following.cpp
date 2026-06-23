#include "HFSMS_Following.h"

#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../HFSMComponent.h"
#include "HFSMS_Wander.h"
#include "GameplayTagsManager.h"
#include "../Transitions/HFSMT_Timer.h"
#include "../Transitions/HFSMT_CheckData.h"

void UHFSMS_Following::BeginPlay(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);

	AddTransition(new HFSMT_Timer(_OwnerComponent->GetStateOfClass<UHFSMS_Wander>(), world, FMath::RandRange(15.f, 25.f)));
}

void UHFSMS_Following::EnterState(APawn* pawn, UWorld* world)
{
	if (_Pedestrian)
	{
		_Pedestrian->SetAnimation(EAnimationType::Walking, true);
		if (auto moveComp = _Pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
		{
			moveComp->SetMovementState(MovementState::Wander);
			moveComp->LeaveLaneForLocation(_Pedestrian->GetClosestFriend()->GetActorLocation());
		}
	}
}