#include "HFSMS_Photographing.h"

#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../HFSMComponent.h"
#include "HFSMS_Wander.h"
#include "GameplayTagsManager.h"
#include "../Transitions/HFSMT_Timer.h"
#include "../Transitions/HFSMT_CheckData.h"

void UHFSMS_Photographing::BeginPlay(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);

	AddTransition(new HFSMT_Timer(_OwnerComponent->GetStateOfClass<UHFSMS_Wander>(), world, FMath::RandRange(20.f, 30.f)));
}

void UHFSMS_Photographing::EnterState(APawn* pawn, UWorld* world)
{
	if (auto moveComp = _Pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetOffLaneAnimationType(EAnimationType::Idle);
		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForSmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Landmark"));
	}
}