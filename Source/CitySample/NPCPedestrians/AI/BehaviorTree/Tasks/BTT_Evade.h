#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "BTT_Evade.generated.h"


UCLASS()
class CITYSAMPLE_API UBTT_Evade : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_Evade() { bNotifyTick = true; }
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

};
