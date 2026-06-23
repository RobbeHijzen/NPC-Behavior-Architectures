#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"

#include "STT_HasFirstTickOccured.generated.h"


USTRUCT()
struct FHasFirstTickOccuredTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor;

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController;

    UPROPERTY(EditAnywhere, Category = Output)
    bool HasFirstTickOccured{ false };
};

USTRUCT(category = "Data", meta = (DisplayName = "HasFirstTickOccured", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTT_HasFirstTickOccured : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FHasFirstTickOccuredTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FHasFirstTickOccuredTaskInstanceData::StaticStruct(); }

    EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
    EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;


private:
};
