#include "BTD_IsAtRedLight.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTD_IsAtRedLight::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) return false;

	APawn* pawn = controller->GetPawn();
	if (!pawn) return false;

	UBlackboardComponent* bb = OwnerComp.GetBlackboardComponent();

	if (bb)
	{
		if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
		{
			bool isAtRedLight{ !moveComp->IsCurrentLaneWalkable() };
			bb->SetValueAsBool(TEXT("IsAtRedLight"), isAtRedLight);
			return isAtRedLight;
		}
	}
	
	return false;
}

void UBTD_IsAtRedLight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) return;

	APawn* pawn = controller->GetPawn();
	if (!pawn) return;

	UBlackboardComponent* bb = OwnerComp.GetBlackboardComponent();

	if (bb)
	{
		if (auto moveComp = pawn->GetComponentByClass<UPedestrianMovementComponent>())
		{
			bb->SetValueAsBool(TEXT("IsAtRedLight"), !moveComp->IsCurrentLaneWalkable());
		}
	}

}
