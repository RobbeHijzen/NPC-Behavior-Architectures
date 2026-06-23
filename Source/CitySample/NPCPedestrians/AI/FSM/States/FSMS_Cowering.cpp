#include "FSMS_Cowering.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../FSMComponent.h"
#include "FSMS_Wander.h"
#include "GameplayTagsManager.h"
#include "../Transitions/FSMT_Timer.h"
#include "../Transitions/FSMT_CheckData.h"
#include "FSMS_Flee.h"
#include "FSMS_React.h"

void UFSMS_Cowering::BeginPlay(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);

	AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Wander>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::LessOrEqual, 0.1f));

	AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Flee>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.5f));
	AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_React>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.3f));
}

void UFSMS_Cowering::EnterState(APawn* pawn, UWorld* world)
{
	if (_Pedestrian)
	{
		_Pedestrian->SetAnimation(EAnimationType::Cower, true);
		if (auto moveComp = _Pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
		{
			moveComp->SetMovementState(MovementState::Idle);
		}
	}
}

void UFSMS_Cowering::TickState(float deltaTime, APawn* pawn)
{
	_Pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	_Pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_Pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}