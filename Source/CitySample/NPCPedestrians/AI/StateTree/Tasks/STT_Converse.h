#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STT_Converse.generated.h"

USTRUCT(category = "Conversing", meta = (DisplayName = "ConverseInstanceData", ToolTip = "", Keywords = ""))
struct FConverseTaskInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<APawn> Actor{};

    UPROPERTY(EditAnywhere, Category = Context, meta = (Context))
    TObjectPtr<AController> AIController{};

    bool DoneWithConversing{ false };

    FTimerHandle ConversingTimerHandle{};
};

USTRUCT(category = "Conversing", meta = (DisplayName = "Converse", ToolTip = "", Keywords = ""))
struct CITYSAMPLE_API FSTT_Converse : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FConverseTaskInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FConverseTaskInstanceData::StaticStruct(); }

    EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
    EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
    void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

};
