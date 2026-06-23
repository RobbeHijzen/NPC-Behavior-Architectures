#include "UAS_WindowShop.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "GameplayTagsManager.h"

void UUAS_WindowShop::BeginPlay(APedestrian* pedestrian, UWorld* world)
{
	_PedestrianReference = pedestrian;
	_PedestrianSmartObj = pedestrian->GetComponentByClass<UPedestrianSmartObjectUserComp>();

}

void UUAS_WindowShop::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetOffLaneAnimationType(EAnimationType::Idle);
		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForSmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.WindowShop"));
	}
}

void UUAS_WindowShop::TickState(float deltaTime, APedestrian* pedestrian)
{
	_PedestrianReference->AddToData("Threat", deltaTime * _ThreatChange);
	_PedestrianReference->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_PedestrianReference->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_WindowShop::UtilityFunction(APedestrian* pedestrian)
{
	return FMath::FRand() * 0.5f * _PedestrianSmartObj->HasNeabySmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.WindowShop"), 3000.f);
}
