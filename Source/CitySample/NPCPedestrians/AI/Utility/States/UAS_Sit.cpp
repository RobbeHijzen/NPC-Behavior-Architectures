#include "UAS_Sit.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "GameplayTagsManager.h"

void UUAS_Sit::BeginPlay(APedestrian* pedestrian, UWorld* world)
{
	_PedestrianReference = pedestrian;
	_PedestrianSmartObj = pedestrian->GetComponentByClass<UPedestrianSmartObjectUserComp>();

}

void UUAS_Sit::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetOffLaneAnimationType(EAnimationType::Sitting);
		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForSmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Seat"));
	}
}

void UUAS_Sit::TickState(float deltaTime, APedestrian* pedestrian)
{
	_PedestrianReference->AddToData("Threat", deltaTime * _ThreatChange);
	_PedestrianReference->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_PedestrianReference->AddToData("Fatigue", deltaTime * _FatigueChange);
	_PedestrianReference->AddToData("Suspicion", deltaTime * _SuspicionChange);
}

float UUAS_Sit::UtilityFunction(APedestrian* pedestrian)
{
	return _PedestrianReference->GetData("Fatigue") / 1.5f * _PedestrianSmartObj->HasNeabySmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Shop"), 3000.f);
}
