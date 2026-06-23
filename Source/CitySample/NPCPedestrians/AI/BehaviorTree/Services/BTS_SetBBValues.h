#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_SetBBValues.generated.h"


UCLASS()
class CITYSAMPLE_API UBTS_SetBBValues : public UBTService
{
	GENERATED_BODY()
	
public:
    UBTS_SetBBValues();

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
