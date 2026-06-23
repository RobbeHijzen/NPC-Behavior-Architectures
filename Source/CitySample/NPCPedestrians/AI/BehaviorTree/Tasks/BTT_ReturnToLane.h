#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"
#include "BTT_ReturnToLane.generated.h"

UCLASS()
class CITYSAMPLE_API UBTT_ReturnToLane : public UBTTaskNode
{
	GENERATED_BODY()
	
	UBTT_ReturnToLane() { bNotifyTick = true; }
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
