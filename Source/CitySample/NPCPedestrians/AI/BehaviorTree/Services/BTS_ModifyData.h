#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_ModifyData.generated.h"

UCLASS()
class CITYSAMPLE_API UBTS_ModifyData : public UBTService
{
	GENERATED_BODY()
	
public:
    UBTS_ModifyData();

    virtual void TickNode(
        UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory,
        float DeltaSeconds
    ) override;

    UPROPERTY(EditAnywhere, Category = "Input")
    FString DataName{};

    UPROPERTY(EditAnywhere, Category = "Input")
    float ValuePerSecond{};
};
