#include "UAS_Shop.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "GameplayTagsManager.h"

void UUAS_Shop::BeginPlay(APedestrian* pedestrian, UWorld* world)
{
	_PedestrianReference = pedestrian;
	_PedestrianSmartObj = pedestrian->GetComponentByClass<UPedestrianSmartObjectUserComp>();
}

void UUAS_Shop::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetOffLaneAnimationType(EAnimationType::Idle);
		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForSmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Shop"));
	}
}

void UUAS_Shop::TickState(float deltaTime, APedestrian* pedestrian)
{
	_PedestrianReference->AddToData("Threat", deltaTime * _ThreatChange);
	_PedestrianReference->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_PedestrianReference->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_Shop::UtilityFunction(APedestrian* pedestrian)
{
	return FMath::FRand() * 0.5f * _PedestrianSmartObj->HasNeabySmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Shop"), 3000.f);
}
