#include "HFSMS_Wander.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../HFSMComponent.h"
#include "GameplayTagsManager.h"

#include "HFSMS_Idle.h"
#include "HFSMS_Flee.h"
#include "HFSMS_React.h"
#include "HFSMS_WindowShop.h"
#include "HFSMS_Converse.h"
#include "HFSMS_Shop.h"
#include "HFSMS_Sit.h"
#include "HFSMS_Work.h"
#include "HFSMS_Wait.h"
#include "HFSMS_Confronting.h"
#include "HFSMS_Cowering.h"
#include "HFSMS_Evading.h"
#include "HFSMS_Following.h"
#include "HFSMS_Investigating.h"
#include "HFSMS_Photographing.h"
#include "HFSMS_Reporting.h"
#include "HFSMS_Spectating.h"


#include "../Transitions/HFSMT_CheckData.h"
#include "../Transitions/HFSMT_HasPendingConversation.h"
#include "../Transitions/HFSMT_IsAtRedLight.h"
#include "../Transitions/HFSMT_RandomChanceSmartObject.h"
#include "../Transitions/HFSMT_ShouldSit.h"
#include "../Transitions/HFSMT_ArePeopleConversing.h"
#include "../Transitions/HFSMT_HasFriendNearby.h"

void UHFSMS_Wander::BeginPlay(APawn* pawn, UWorld* world)
{
	switch (_OwnerComponent->GetComplexityLevel())
	{
	case HFSMComplexityLevel::Simple:
	{
		AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Idle>(), world, Cast<APedestrian>(pawn), "Fatigue", EFloatComparison::GreaterOrEqual, 0.75f));

		break;
	}
	case HFSMComplexityLevel::Medium:
	{
		AddTransition(new HFSMT_ShouldSit(_OwnerComponent->GetStateOfClass<UHFSMS_Sit>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new HFSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UHFSMS_Work>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Work")));
		AddTransition(new HFSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UHFSMS_Shop>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Shop")));
		AddTransition(new HFSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UHFSMS_WindowShop>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.WindowShop")));
		AddTransition(new HFSMT_IsAtRedLight(_OwnerComponent->GetStateOfClass<UHFSMS_Wait>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new HFSMT_HasPendingConversation(_OwnerComponent->GetStateOfClass<UHFSMS_Converse>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Converse>(), world, Cast<APedestrian>(pawn), "SocialNeed", EFloatComparison::GreaterOrEqual, 0.75f));

		AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Idle>(), world, Cast<APedestrian>(pawn), "Fatigue", EFloatComparison::GreaterOrEqual, 0.75f));

		break;
	}
	case HFSMComplexityLevel::High:
	{
		AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Reporting>(), world, Cast<APedestrian>(pawn), "Suspicion", EFloatComparison::GreaterOrEqual, 0.9f));
		AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Investigating>(), world, Cast<APedestrian>(pawn), "Suspicion", EFloatComparison::GreaterOrEqual, 0.5f));
		AddTransition(new HFSMT_HasFriendNearby(_OwnerComponent->GetStateOfClass<UHFSMS_Following>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new HFSMT_ArePeopleConversing(_OwnerComponent->GetStateOfClass<UHFSMS_Confronting>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new HFSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UHFSMS_Photographing>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Landmark")));
		AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Cowering>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.9f));
		AddTransition(new HFSMT_ArePeopleConversing(_OwnerComponent->GetStateOfClass<UHFSMS_Spectating>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Evading>(), world, Cast<APedestrian>(pawn), "Suspicion", EFloatComparison::GreaterOrEqual, 0.2f));


		AddTransition(new HFSMT_ShouldSit(_OwnerComponent->GetStateOfClass<UHFSMS_Sit>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new HFSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UHFSMS_Work>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Work")));
		AddTransition(new HFSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UHFSMS_Shop>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.Shop")));
		AddTransition(new HFSMT_RandomChanceSmartObject(_OwnerComponent->GetStateOfClass<UHFSMS_WindowShop>(), world, Cast<APedestrian>(pawn), UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.WindowShop")));
		AddTransition(new HFSMT_IsAtRedLight(_OwnerComponent->GetStateOfClass<UHFSMS_Wait>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new HFSMT_HasPendingConversation(_OwnerComponent->GetStateOfClass<UHFSMS_Converse>(), world, Cast<APedestrian>(pawn)));
		AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Converse>(), world, Cast<APedestrian>(pawn), "SocialNeed", EFloatComparison::GreaterOrEqual, 0.75f));

		AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Idle>(), world, Cast<APedestrian>(pawn), "Fatigue", EFloatComparison::GreaterOrEqual, 0.75f));
		AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_Flee>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.5f));
		AddTransition(new HFSMT_CheckData(_OwnerComponent->GetStateOfClass<UHFSMS_React>(), world, Cast<APedestrian>(pawn), "Threat", EFloatComparison::GreaterOrEqual, 0.3f));

		break;
	}
	}


}

void UHFSMS_Wander::EnterState(APawn* pawn, UWorld* world)
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

void UHFSMS_Wander::TickState(float deltaTime, APawn* pawn)
{
	_Pedestrian->AddToData("Fatigue", deltaTime * _FatigueChange);
}