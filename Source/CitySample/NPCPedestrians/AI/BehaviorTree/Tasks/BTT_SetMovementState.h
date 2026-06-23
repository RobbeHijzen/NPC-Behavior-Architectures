#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../../../Pedestrians/PedestrianMovementComponent.h"

#include "BTT_SetMovementState.generated.h"


UCLASS()
class CITYSAMPLE_API UBTT_SetMovementState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTT_SetMovementState() {}

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category="Input")
	MovementState _NewMovementState{};
};
