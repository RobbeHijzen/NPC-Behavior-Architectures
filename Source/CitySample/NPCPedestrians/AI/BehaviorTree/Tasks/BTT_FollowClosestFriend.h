#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

#include "BTT_FollowClosestFriend.generated.h"


UCLASS()
class CITYSAMPLE_API UBTT_FollowClosestFriend : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_FollowClosestFriend() { bNotifyTick = true; }
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	APedestrian* _ClosestFriend{};
	UPedestrianMovementComponent* _MoveComp{};
};
