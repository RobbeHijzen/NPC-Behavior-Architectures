#include "FSMS_Wander.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../FSMComponent.h"
#include "GameplayTagsManager.h"

#include "FSMS_Idle.h"
#include "FSMS_Flee.h"
#include "FSMS_React.h"
#include "FSMS_WindowShop.h"
#include "FSMS_Converse.h"
#include "FSMS_Shop.h"
#include "FSMT_Sit.h"
#include "FSMS_Work.h"
#include "FSMS_Wait.h"

#include "FSMS_Confronting.h"
#include "FSMS_Cowering.h"
#include "FSMS_Evading.h"
#include "FSMS_Following.h"
#include "FSMS_Investigating.h"
#include "FSMS_Photographing.h"
#include "FSMS_Reporting.h"
#include "FSMS_Spectating.h"

#include "../Transitions/FSMT_CheckData.h"
#include "../Transitions/FSMT_HasPendingConversation.h"
#include "../Transitions/FSMT_IsAtRedLight.h"
#include "../Transitions/FSMT_RandomChanceSmartObject.h"
#include "../Transitions/FSMT_ShouldSit.h"
#include "../Transitions/FSMT_ArePeopleConversing.h"
#include "../Transitions/FSMT_HasFriendNearby.h"

void UFSMS_Wander::BeginPlay(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);

	switch (_OwnerComponent->GetComplexityLevel())
	{
	case FSMComplexityLevel::Simple:
	{
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Idle>(), world, Cast<APedestrian>(pawn), "Fatigue", EFloatComparison::GreaterOrEqual, 0.75f));
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Flee>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.5f));
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_React>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.3f));

		break;
	}
	case FSMComplexityLevel::Medium:
	{
		AddTransition(new FSMT_ShouldSit(_OwnerComponent->GetStateOfClass<UFSMT_Sit>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new FSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UFSMS_Work>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Work")));
		AddTransition(new FSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UFSMS_Shop>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Shop")));
		AddTransition(new FSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UFSMS_WindowShop>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.WindowShop")));
		AddTransition(new FSMT_IsAtRedLight(_OwnerComponent->GetStateOfClass<UFSMS_Wait>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new FSMT_HasPendingConversation(_OwnerComponent->GetStateOfClass<UFSMS_Converse>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Converse>(), world, Cast<APedestrian>(pawn), "SocialNeed", EFloatComparison::GreaterOrEqual, 0.75f));
		
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Idle>(), world, Cast<APedestrian>(pawn), "Fatigue", EFloatComparison::GreaterOrEqual, 0.75f));
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Flee>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.5f));
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_React>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.3f));

		break;
	}
	case FSMComplexityLevel::High:
	{
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Reporting>(), world, Cast<APedestrian>(pawn), "Suspicion", EFloatComparison::GreaterOrEqual, 0.9f));
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Investigating>(), world, Cast<APedestrian>(pawn), "Suspicion", EFloatComparison::GreaterOrEqual, 0.5f));
		AddTransition(new FSMT_HasFriendNearby(_OwnerComponent->GetStateOfClass<UFSMS_Following>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new FSMT_ArePeopleConversing(_OwnerComponent->GetStateOfClass<UFSMS_Confronting>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new FSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UFSMS_Photographing>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Landmark")));
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Cowering>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.9f));
		AddTransition(new FSMT_ArePeopleConversing(_OwnerComponent->GetStateOfClass<UFSMS_Spectating>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Evading>(), world, Cast<APedestrian>(pawn), "Suspicion", EFloatComparison::GreaterOrEqual, 0.2f));


		AddTransition(new FSMT_ShouldSit(_OwnerComponent->GetStateOfClass<UFSMT_Sit>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new FSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UFSMS_Work>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Work")));
		AddTransition(new FSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UFSMS_Shop>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Shop")));
		AddTransition(new FSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UFSMS_WindowShop>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.WindowShop")));
		AddTransition(new FSMT_IsAtRedLight(_OwnerComponent->GetStateOfClass<UFSMS_Wait>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new FSMT_HasPendingConversation(_OwnerComponent->GetStateOfClass<UFSMS_Converse>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Converse>(), world, Cast<APedestrian>(pawn), "SocialNeed", EFloatComparison::GreaterOrEqual, 0.75f));

		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Idle>(), world, Cast<APedestrian>(pawn), "Fatigue", EFloatComparison::GreaterOrEqual, 0.75f));
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_Flee>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.5f));
		AddTransition(new FSMT_CheckData(_OwnerComponent->GetStateOfClass<UFSMS_React>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.3f));

		break;
	}
	}


}

void UFSMS_Wander::EnterState(APawn* pawn, UWorld* world)
{
	_Pedestrian = Cast<APedestrian>(pawn);
	if (_Pedestrian)
	{
		_Pedestrian->SetAnimation(EAnimationType::Walking, true);
	}

	if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetMovementState(MovementState::Wander);
	}
}

void UFSMS_Wander::TickState(float deltaTime, APawn* pawn)
{
	_Pedestrian->AddToData("Threat", deltaTime * _ThreatChange);
	_Pedestrian->AddToData("Fatigue", deltaTime * _FatigueChange);
	_Pedestrian->AddToData("SocialNeed", deltaTime * _SocialNeedChange);
	_Pedestrian->AddToData("Suspicion", deltaTime * _SuspicionChange);

}