#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "BTT_Converse.generated.h"


UCLASS()
class CITYSAMPLE_API UBTT_Converse : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_Converse() { bNotifyTick = true; }
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	FTimerHandle _ConversingTimerHandle{};
	bool _DoneWithConversing{ false };

};
