#include "UAS_Photographing.h"


void UUAS_Photographing::BeginPlay(APedestrian* pedestrian, UWorld* world)
{
	_PedestrianSmartObj = pedestrian->GetComponentByClass<UPedestrianSmartObjectUserComp>();
}

void UUAS_Photographing::EnterState(APedestrian* pedestrian, UWorld* world)
{
	if (auto moveComp = pedestrian->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetOffLaneAnimationType(EAnimationType::Idle);
		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForSmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Landmark"));
	}
}

void UUAS_Photographing::TickState(float deltaTime, APedestrian* pedestrian)
{
	pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}

float UUAS_Photographing::UtilityFunction(APedestrian* pedestrian)
{
	return FMath::FRand() * 0.5f * _PedestrianSmartObj->HasNeabySmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Landmark"), 3000.f);
}