#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "AIC_BT_Base.generated.h"


UCLASS()
class CITYSAMPLE_API AAIC_BT_Base : public AAIController
{
    GENERATED_BODY()

public:
    virtual void OnPossess(APawn* InPawn) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TObjectPtr<UBehaviorTree> _BehaviorTree{};
};
