#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "BTT_MoveToSuspicion.generated.h"


UCLASS()
class CITYSAMPLE_API UBTT_MoveToSuspicion : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_MoveToSuspicion() { bNotifyTick = true; }
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
