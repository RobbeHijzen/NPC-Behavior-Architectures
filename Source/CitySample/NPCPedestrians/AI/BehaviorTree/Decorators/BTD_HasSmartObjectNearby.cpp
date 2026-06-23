#include "BTD_HasSmartObjectNearby.h"
#include "AIController.h"
#include "../../../Pedestrians/PedestrianSmartObjectUserComp.h"

bool UBTD_HasSmartObjectNearby::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) return false;

	APawn* pawn = controller->GetPawn();
	if (!pawn) return false;

	if (auto userComp = pawn->GetComponentByClass<UPedestrianSmartObjectUserComp>())
	{
		return userComp->HasNeabySmartObject(_SmartObjectTag, _Range);
	}

	return false;
}
