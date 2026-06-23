#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "BTT_PlayAnimation.generated.h"


UCLASS()
class CITYSAMPLE_API UBTT_PlayAnimation : public UBTTaskNode
{
	GENERATED_BODY()
	
	UBTT_PlayAnimation() { bNotifyTick = true; }
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	EAnimationType _AnimationType{};

	UPROPERTY(EditAnywhere, Category = "Input")
	bool _LoopAnimation{};

	UPROPERTY(EditAnywhere, Category = "Input")
	bool _DoSucceed{ true };

	FTimerHandle _TimerHandle{};
	bool _HasFinishedAnimation{ false };
};
