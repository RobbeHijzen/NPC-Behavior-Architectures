#include "FSMT_Sit.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../FSMComponent.h"
#include "FSMS_Wander.h"
#include "GameplayTagsManager.h"
#include "../Transitions/FSMT_CheckData.h"
#include "FSMS_Flee.h"
#include "FSMS_React.h"

void UFSMT_Sit::BeginPlay(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);

	AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Wander>(), world, Cast<APedestrian>(pawn), "Fatigue", EFloatComparison::Equal, 0.f));

	AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Flee>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.5f));
	AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_React>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.3f));
}

void UFSMT_Sit::EnterState(APawn* pawn, UWorld* world)
{
	if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetOffLaneAnimationType(EAnimationType::Sitting);
		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForSmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Seat"));
	}
}

void UFSMT_Sit::TickState(float deltaTime, APawn* pawn)
{
	_Pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	_Pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_Pedestrian->AddToData("Fatigue", deltaTime * _FatigueChange);
	_Pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}