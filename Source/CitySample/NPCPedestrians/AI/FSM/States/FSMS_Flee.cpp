#include "FSMS_Flee.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../Transitions/FSMT_CheckData.h"
#include "../FSMComponent.h"
#include "FSMS_Wander.h"

void UFSMS_Flee::BeginPlay(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);

	AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Wander>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::LessOrEqual, 0.2f));
}

void UFSMS_Flee::EnterState(APawn* pawn, UWorld* world)
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

void UFSMS_Flee::TickState(float deltaTime, APawn* pawn)
{
	_Pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	_Pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_Pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}