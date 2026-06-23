#include "HFSMS_Sit.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../HFSMComponent.h"
#include "HFSMS_Wander.h"
#include "GameplayTagsManager.h"
#include "../Transitions/HFSMT_CheckData.h"

void UHFSMS_Sit::BeginPlay(APawn* pawn, UWorld* world)
{
	AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Wander>(), world, Cast<APedestrian>(pawn), "Fatigue", EFloatComparison::Equal, 0.f));
}

void UHFSMS_Sit::EnterState(APawn* pawn, UWorld* world)
{
	if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetOffLaneAnimationType(EAnimationType::Sitting);
		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForSmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Seat"));
	}
}

void UHFSMS_Sit::TickState(float deltaTime, APawn* pawn)
{
	_Pedestrian->AddToData("SocialNeed", deltaTime * _FatigueChange);

}
