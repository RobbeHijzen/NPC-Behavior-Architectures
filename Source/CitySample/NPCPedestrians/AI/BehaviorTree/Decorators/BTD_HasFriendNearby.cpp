#include "BTD_HasFriendNearby.h"
#include "AIController.h"
#include "../../../Pedestrians/PedestrianSmartObjectUserComp.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../../Pedestrians/NPCSpatialGrid.h"

bool UBTD_HasFriendNearby::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) return EBTNodeResult::Failed;

	APawn* pawn = controller->GetPawn();
	if (!pawn) return EBTNodeResult::Failed;

	APedestrian* ownerPedestrian = Cast<APedestrian>(pawn);
	if (!ownerPedestrian) return EBTNodeResult::Failed;

	int friendGroup{ ownerPedestrian->GetFriendGroup() };

	TArray<AActor*> actors{};
	GetWorld()->GetSubsystem<UNPCSpatialGrid>()->QueryRadius(ownerPedestrian->GetActorLocation(), 200.f, actors);

	for (auto actor : actors)
	{
		if (actor == ownerPedestrian) continue;

		if (auto pedestrian = Cast<APedestrian>(actor))
		{
			if (friendGroup == pedestrian->GetFriendGroup())
			{
				ownerPedestrian->SetClosestFriend(pedestrian);
				return true;
			}
		}
	}

	return false;
}
