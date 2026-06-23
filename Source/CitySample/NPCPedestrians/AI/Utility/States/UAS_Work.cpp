#include "UAS_Work.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "GameplayTagsManager.h"

void UUAS_Work::BeginPlay(APedestrian* pedestrian, UWorld* world)
{
	_PedestrianReference = pedestrian;
	_PedestrianSmartObj = pedestrian->GetComponentByClass<UPedestrianSmartObjectUserComp>();

}

void UUAS_Work::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetOffLaneAnimationType(EAnimationType::Idle);
		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForSmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Work"));
	}
}

void UUAS_Work::TickState(float deltaTime, APedestrian* pedestrian)
{
	_PedestrianReference->AddToData("Threat", deltaTime * _ThreatChange);
	_PedestrianReference->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_PedestrianReference->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_Work::UtilityFunction(APedestrian* pedestrian)
{
	return FMath::FRand() * 0.5f * _PedestrianSmartObj->HasNeabySmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Work"), 3000.f);
}
