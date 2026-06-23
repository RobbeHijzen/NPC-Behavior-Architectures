#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../../../Pedestrians/Pedestrian.h"

#include "BTT_Confront.generated.h"


UCLASS()
class CITYSAMPLE_API UBTT_Confront : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_Confront() { bNotifyTick = true; }
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = Input)
	float _DistancePercentage{ 1.f };
};
