#include "FSMS_Work.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../FSMComponent.h"
#include "FSMS_Wander.h"
#include "GameplayTagsManager.h"
#include "../Transitions/FSMT_Timer.h"
#include "../Transitions/FSMT_CheckData.h"
#include "FSMS_Flee.h"
#include "FSMS_React.h"

void UFSMS_Work::BeginPlay(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);

	AddTransition(new FSMT_Timer(_OwnerComponent->GetStateOfClass<UFSMS_Wander>(), world, FMath::RandRange(40.f, 60.f)));
	
	AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Flee>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.5f));
	AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_React>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.3f));
}

void UFSMS_Work::EnterState(APawn* pawn, UWorld* world)
{
	if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetOffLaneAnimationType(EAnimationType::Idle);
		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForSmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Work"));
	}
}

void UFSMS_Work::TickState(float deltaTime, APawn* pawn)
{
	_Pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	_Pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_Pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}