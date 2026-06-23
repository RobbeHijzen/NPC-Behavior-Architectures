#include "HFSMS_Spectating.h"

#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../HFSMComponent.h"
#include "HFSMS_Wander.h"
#include "GameplayTagsManager.h"
#include "../Transitions/HFSMT_Timer.h"
#include "../Transitions/HFSMT_CheckData.h"

void UHFSMS_Spectating::BeginPlay(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);

	AddTransition(new HFSMT_Timer(_OwnerComponent->GetStateOfClass<UHFSMS_Wander>(), world, FMath::RandRange(15.f, 25.f)));
}

void UHFSMS_Spectating::EnterState(APawn* pawn, UWorld* world)
{
	if (auto moveComp = _Pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		_Pedestrian->SetAnimation(EAnimationType::Walking, true);
		moveComp->SetMovementState(MovementState::Wander);

		moveComp->LeaveLaneForLocation(_Pedestrian->GetActorLocation() + 0.5f * (_Pedestrian->GetConfrontTransform().GetLocation() - _Pedestrian->GetActorLocation()));
	}
}