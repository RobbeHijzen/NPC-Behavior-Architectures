#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../../../Pedestrians/Pedestrian.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

#include "BTT_LeaveLaneForSmartObject.generated.h"


UCLASS()
class CITYSAMPLE_API UBTT_LeaveLaneForSmartObject : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_LeaveLaneForSmartObject() { bNotifyTick = true; }
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UPROPERTY(EditAnywhere, Category = Input)
    FGameplayTag _SmartObjectTag{};

    UPROPERTY(EditAnywhere, Category = Input)
    EAnimationType _AnimationTypeWhenAtLocation{};

    UPedestrianMovementComponent* _MoveComp{};
};
