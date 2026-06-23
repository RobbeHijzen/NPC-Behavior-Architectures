#include "HFSMS_WindowShop.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "../HFSMComponent.h"
#include "HFSMS_Wander.h"
#include "GameplayTagsManager.h"
#include "../Transitions/HFSMT_Timer.h"

void UHFSMS_WindowShop::BeginPlay(APawn* pawn, UWorld* world)
{
	AddTransition(new HFSMT_Timer(_OwnerComponent->GetStateOfClass<UHFSMS_Wander>(), world, FMath::RandRange(20.f, 40.f)));
}

void UHFSMS_WindowShop::EnterState(APawn* pawn, UWorld* world)
{
	if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
	{
		moveComp->SetOffLaneAnimationType(EAnimationType::Idle);
		moveComp->SetMovementState(MovementState::Wander);
		moveComp->LeaveLaneForSmartObject(UGameplayTagsManager::Get().RequestGameplayTag("SmartObjects.WindowShop"));
	}
}